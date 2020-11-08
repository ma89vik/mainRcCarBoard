/**
 * Copyright 2020 Marius
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "fxos8700.h"

#include "app_i2c.h"
#include "log.h"
#include "error_def.h"

#include "FreeRTOS.h"

#include <stdbool.h>
#include <stdint.h>


#define FXOS8700CQ_SLAVE_ADDR     0x1E   
#define FXOS8700CQ_STATUS         0x00
#define FXOS8700CQ_WHOAMI         0x0D
#define FXOS8700CQ_XYZ_DATA_CFG   0x0E
#define FXOS8700CQ_CTRL_REG1      0x2A
#define FXOS8700CQ_M_CTRL_REG1    0x5B
#define FXOS8700CQ_M_CTRL_REG2    0x5C
#define FXOS8700CQ_WHOAMI_VAL     0xC7


#define FXOS8700CQ_READ_LEN    13   




static app_i2c_handle_t* s_i2c_handle;

static err_def_t fxos8700_read_reg(uint8_t address, uint8_t* data, size_t len)
{
    err_def_t err;

    err = app_i2c_read_reg(s_i2c_handle, FXOS8700CQ_SLAVE_ADDR, address, data, len, portMAX_DELAY);

    return err;
}

static err_def_t fxos8700_write_reg(uint8_t address, uint8_t data)
{
    err_def_t err;

    err = app_i2c_write_reg(s_i2c_handle, FXOS8700CQ_SLAVE_ADDR, address, &data, 1, portMAX_DELAY);

    return err;
}

/*
static bool fxos8700_write_reg(uint8_t address, uint8_t data)
{
    uint32_t err;
    uint8_t datas[2];

    datas[0] = address;
    datas[1] = data;
    err = i2c_write(&deviceI2c, MPU_9250_ADDRESS, datas, 2);
    return (err == I2C_OK);
}

bool fxos8700_read_gyro(int16_t *x, int16_t *y, int16_t *z)
{
    uint8_t recv_buf[6];

    fxos8700_read_reg(GYRO_ADDRESS, recv_buf, 6);

    *x = (int16_t)(((int16_t)recv_buf[0] << 8) | recv_buf[1]);
    *y = (int16_t)(((int16_t)recv_buf[2] << 8) | recv_buf[3]);
    *z = (int16_t)(((int16_t)recv_buf[4] << 8) | recv_buf[5]);
}

bool fxos8700_read_gyro_yaw_rate(int16_t *z)
{
    uint8_t recv_buf[2];

    fxos8700_read_reg(GYRO_YAW_ADDRESS, recv_buf, 2);

    *z = (int16_t)(((int16_t)recv_buf[4] << 8) | recv_buf[5]);
}

bool fxos8700_read_accel(int16_t *x, int16_t *y, int16_t *z)
{
    uint8_t recv_buf[6];

    fxos8700_read_reg(ACCEL_ADDRESS, recv_buf, 6);

    *x = (int16_t)(((int16_t)recv_buf[0] << 8) | recv_buf[1]);
    *y = (int16_t)(((int16_t)recv_buf[2] << 8) | recv_buf[3]);
    *z = (int16_t)(((int16_t)recv_buf[4] << 8) | recv_buf[5]);
}

bool fxos8700_read_accel_xy(int16_t *x, int16_t *y)
{
    uint8_t recv_buf[6];

    fxos8700_read_reg(ACCEL_ADDRESS, recv_buf, 6);

    *x = (int16_t)(((int16_t)recv_buf[0] << 8) | recv_buf[1]);
    *y = (int16_t)(((int16_t)recv_buf[2] << 8) | recv_buf[3]);
}
*/

static bool fxos8700_check_id(uint8_t expected_id)
{
    uint8_t value;
    fxos8700_read_reg(FXOS8700CQ_WHOAMI, &value, 1);
    LOG_DEBUG("FXOS8700 WHOAMI value = %X, expected %X\n", value, expected_id);

    return (expected_id == value);
}


err_def_t fxos8700_init(app_i2c_handle_t* i2c_handle)
{
    uint8_t val;
    s_i2c_handle = i2c_handle;

    
    /* Read and verify device ID */
    if (!fxos8700_check_id(FXOS8700CQ_WHOAMI_VAL))
    {
        LOG_ERROR("FXOS8700 init failed\n");
        return ERR_FAIL;
    }

    /* Set to standby to configure */
    val = 0x0;
    fxos8700_write_reg(FXOS8700CQ_CTRL_REG1, val);

    /*
    [7]: m_acal=0: auto calibration disabled
    [6]: m_rst=0: no one-shot magnetic reset
    [5]: m_ost=0: no one-shot magnetic measurement
    [4-2]: m_os=111=7: 8x oversampling (for 200Hz) to reduce magnetometer noise
    [1-0]: m_hms=11=3: select hybrid mode with accel and magnetometer active */
    val = 0b00011111;
    fxos8700_write_reg(FXOS8700CQ_M_CTRL_REG1, val);

    /*  
    [7]: reserved
    [6]: reserved
    [5]: hyb_autoinc_mode=1 to map the magnetometer registers to follow the 
    accelerometer registers
    [4]: m_maxmin_dis=0 to retain default min/max latching even though not used
    [3]: m_maxmin_dis_ths=0
    [2]: m_maxmin_rst=0
    [1-0]: m_rst_cnt=00 to enable magnetic reset each cycle */
    val = 0b00100000;
    fxos8700_write_reg(FXOS8700CQ_M_CTRL_REG2, val);

    /*
    [7]: reserved
    [6]: reserved
    [5]: reserved
    [4]: hpf_out=0
    [3]: reserved
    [2]: reserved
    [1-0]: fs=01 for accelerometer range of +/-4g range with 0.488mg/LSB
    */
    val = 0b00000001;
    fxos8700_write_reg(FXOS8700CQ_XYZ_DATA_CFG, val);

    /* write 0000 1101 = 0x0D to accelerometer control register 1
    [7-6]: aslp_rate=00
    [5-3]: dr=001 for 200Hz data rate (when in hybrid mode)
    [2]: lnoise=1 for low noise mode
    [1]: f_read=0 for normal 16 bit reads
    [0]: active=1 to take the part out of standby and enable samplingdataby
    */
    val = 0b00001101;
    fxos8700_write_reg(FXOS8700CQ_CTRL_REG1, val);

    LOG_DEBUG("FXOS8700 initialized");

    return ERR_OK;
}

void fxso8700_read_data(xyz_data_t *accel_data, xyz_data_t* mag_data)
{
    uint8_t buf[FXOS8700CQ_READ_LEN];

    fxos8700_read_reg(FXOS8700CQ_STATUS, buf, FXOS8700CQ_READ_LEN);

    // copy the 14 bit accelerometer byte data into 16 bit words*/
    accel_data->x = (int16_t)(((buf[1] << 8) | buf[2]))>> 2;
    accel_data->y = (int16_t)(((buf[3] << 8) | buf[4]))>> 2;
    accel_data->z = (int16_t)(((buf[5] << 8) | buf[6]))>> 2;
    // copy the magnetometer byte data into 16 bit words*/
    mag_data->x = (buf[7] << 8) | buf[8];
    mag_data->y = (buf[9] << 8) | buf[10];
    mag_data->z = (buf[11] << 8) | buf[12];

    LOG_DEBUG("FXOS raw accelerometer data: x = %d, y = %d, z = %d\n", accel_data->x, accel_data->y, accel_data->z);
    LOG_DEBUG("FXOS raw magnetometer data: x = %d, y = %d, z = %d\n", mag_data->x, mag_data->y, mag_data->z);

}