#include "board.h"
#include "i2c_device.h"
#include "log.h"

#include <stddef.h>
#include <stdint.h>

#define MPU_9250_ADDRESS 0b1101000U
#define WHO_AM_I_ADDRESS 0x75U
#define RESET_ADDRESS 0x68U
#define GYRO_ADDRESS 0x43U
#define GYRO_YAW_ADDRESS 0x47U
#define ACCEL_ADDRESS 0x3BU
#define BYPASS_ADDRESS 0x37U

static const uint8_t expected_who_am_i = 0x71U;

static bool mpu9250_read_reg(uint8_t address, uint8_t *p_data, size_t len)
{

    uint32_t err;

    err = i2c_write(&deviceI2c, MPU_9250_ADDRESS, &address, 1);
    err = i2c_read(&deviceI2c, MPU_9250_ADDRESS, p_data, len);

    return (err == I2C_OK);
}

static bool mpu9250_write_reg(uint8_t address, uint8_t data)
{
    uint32_t err;
    uint8_t datas[2];

    datas[0] = address;
    datas[1] = data;
    err = i2c_write(&deviceI2c, MPU_9250_ADDRESS, datas, 2);
    return (err == I2C_OK);
}

bool mpu9250_read_gyro(int16_t *x, int16_t *y, int16_t *z)
{
    uint8_t recv_buf[6];

    mpu9250_read_reg(GYRO_ADDRESS, recv_buf, 6);

    *x = (int16_t)(((int16_t)recv_buf[0] << 8) | recv_buf[1]);
    *y = (int16_t)(((int16_t)recv_buf[2] << 8) | recv_buf[3]);
    *z = (int16_t)(((int16_t)recv_buf[4] << 8) | recv_buf[5]);
}

bool mpu9250_read_gyro_yaw_rate(int16_t *z)
{
    uint8_t recv_buf[2];

    mpu9250_read_reg(GYRO_YAW_ADDRESS, recv_buf, 2);

    *z = (int16_t)(((int16_t)recv_buf[4] << 8) | recv_buf[5]);
}

bool mpu9250_read_accel(int16_t *x, int16_t *y, int16_t *z)
{
    uint8_t recv_buf[6];

    mpu9250_read_reg(ACCEL_ADDRESS, recv_buf, 6);

    *x = (int16_t)(((int16_t)recv_buf[0] << 8) | recv_buf[1]);
    *y = (int16_t)(((int16_t)recv_buf[2] << 8) | recv_buf[3]);
    *z = (int16_t)(((int16_t)recv_buf[4] << 8) | recv_buf[5]);
}

bool mpu9250_read_accel_xy(int16_t *x, int16_t *y)
{
    uint8_t recv_buf[6];

    mpu9250_read_reg(ACCEL_ADDRESS, recv_buf, 6);

    *x = (int16_t)(((int16_t)recv_buf[0] << 8) | recv_buf[1]);
    *y = (int16_t)(((int16_t)recv_buf[2] << 8) | recv_buf[3]);
}

static bool mpu9250_check_id(uint8_t expected_id)
{
    uint8_t value;
    mpu9250_read_reg(WHO_AM_I_ADDRESS, &value, 1);

    return (expected_id == value);
}

bool mpu9250_init()
{
    uint8_t data = WHO_AM_I_ADDRESS;
    uint32_t err;

    // Reset device (Gyro - accel - temperature)
    uint8_t reset_val = 0b111U;
    mpu9250_write_reg(RESET_ADDRESS, reset_val);

    // Activate bypass for i2c, required for magnetometer
    uint8_t bypass_en_val = 0b10;
    mpu9250_write_reg(BYPASS_ADDRESS, bypass_en_val);

    // Read and verify device ID
    if (!mpu9250_check_id(expected_who_am_i))
    {
        LOG_ERROR("MPU9250 init failed\n");
        return false;
    }

    return true;
}
