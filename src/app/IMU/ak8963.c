#include "board.h"
#include "i2c_device.h"
#include "log.h"

#include <stddef.h>
#include <stdint.h>

// Register addresses for the MPU9250's magnetometer (AK8963)
#define AK8963_ADDRESS 0x0C
#define WHO_AM_I_ADDRESS 0x00U
#define MAG_DATA_ADDRESS 0x03U
#define MAG_STA2_ADDRESS 0x09U
#define MAG_CTRL1_ADDRESS 0x0AU
#define MAG_CTRL2_ADDRESS 0x0BU

static const uint8_t expected_who_am_i = 0x48U;

static bool ak8963_read_reg(uint8_t address, uint8_t *p_data, size_t len)
{

    uint32_t err;

    err = i2c_write(&deviceI2c, AK8963_ADDRESS, &address, 1);
    err = i2c_read(&deviceI2c, AK8963_ADDRESS, p_data, len);

    return (err == I2C_OK);
}

static bool ak8963_write_reg(uint8_t address, uint8_t data)
{
    uint32_t err;
    uint8_t datas[2];

    datas[0] = address;
    datas[1] = data;
    err = i2c_write(&deviceI2c, AK8963_ADDRESS, datas, 2);
    return (err == I2C_OK);
}

bool ak8963_read_mag(int16_t *x, int16_t *y, int16_t *z)
{
    uint8_t recv_buf[6];

    ak8963_read_reg(MAG_DATA_ADDRESS, recv_buf, 6);

    *x = (int16_t)(((int16_t)recv_buf[0] << 8) | recv_buf[1]);
    *y = (int16_t)(((int16_t)recv_buf[2] << 8) | recv_buf[3]);
    *z = (int16_t)(((int16_t)recv_buf[4] << 8) | recv_buf[5]);

    // Need to read status 2 to signal that reading is done

    ak8963_read_reg(MAG_STA2_ADDRESS, recv_buf, 1);
}

static bool ak8963_check_id(uint8_t expected_id)
{
    uint8_t value;
    ak8963_read_reg(WHO_AM_I_ADDRESS, &value, 1);

    return (expected_id == value);
}

bool ak8963_init()
{
    uint8_t data = WHO_AM_I_ADDRESS;
    uint32_t err;

    // Soft reset device
    uint8_t reset_val = 0b1U;
    ak8963_write_reg(MAG_CTRL2_ADDRESS, reset_val);

    // Read and verify device ID
    if (!ak8963_check_id(expected_who_am_i))
    {
        LOG_ERROR("ak8963 init failed\n");
        return false;
    }
    // Configure for continous reading
    uint8_t cont_read_val = 0b10U;
    ak8963_write_reg(MAG_CTRL1_ADDRESS, cont_read_val);

    return true;
}