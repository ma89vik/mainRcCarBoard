#ifndef I2C_DEVICE_H_
#define I2C_DEVICE_H_

#include "device.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef enum I2cResult
{
    I2C_NONE = -1,
    I2C_OK,
    I2C_ERR_INSTANCE,
    I2C_ERR_CONFIG,
    I2C_ERR_TX,
    I2C_ERR_RX,
    I2C_BUSY,
} I2cResult_t;

typedef struct I2cConfig
{
    I2cResult_t (*init)(Device_t *dev);   

} I2cConfig_t;

typedef struct I2cApi
{
    I2cResult_t (*i2c_write)(Device_t *dev, uint8_t address, uint8_t *p_data, size_t length);
    I2cResult_t (*i2c_read)(Device_t *dev, uint8_t address, uint8_t *p_data, size_t length);
} I2cApi_t;

static inline I2cResult_t i2c_init(Device_t *dev)
{
    I2cConfig_t *cfg = (I2cConfig_t *)(dev->driverConfig);
    if (!cfg)
    {
        return I2C_ERR_CONFIG;
    }

    return cfg->init(dev);
}

static inline I2cResult_t i2c_write(Device_t *dev, uint8_t address,
                                    uint8_t *p_data, size_t length)
{
    if (!dev)
    {
        return I2C_ERR_INSTANCE;
    }

    I2cApi_t *api = (I2cApi_t *)(dev->driverApi);

    if (api->i2c_write)
    {
        return api->i2c_write(dev, address, p_data, length);
    }

    return I2C_ERR_INSTANCE;
}

static inline I2cResult_t i2c_read(Device_t *dev, uint8_t address,
                                   uint8_t *p_data, size_t length)
{
    if (!dev)
    {
        return -1;
    }

    I2cApi_t *api;
    api = (I2cApi_t *)(dev->driverApi);

    if (api->i2c_read)
    {
        return api->i2c_read(dev, address, p_data, length);
    }

    return I2C_ERR_INSTANCE;
}

#endif