#include "i2c_stm32.h"
#include "board.h"
#include "device.h"
#include "i2c_device.h"
#include "log.h"

#include "i2c.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


I2cApi_t stm32_i2c_api = {.i2c_read = stm32_i2c_read,
                          .i2c_write = stm32_i2c_write};


I2cResult_t stm32_i2c_init(Device_t *dev)
{
    if (!dev)
    {
        return I2C_ERR_INSTANCE;
    }
    uint32_t err_code;

    I2cDriverData_t *i2cData = (I2cDriverData_t *)(dev->driverData);
    I2cConfig_t *i2cConfig = (I2cConfig_t *)(dev->driverConfig);

    dev->driverApi = &stm32_i2c_api;


    return I2C_OK;
}

I2cResult_t stm32_i2c_write(Device_t* dev, uint8_t address, uint8_t *p_data, size_t length)
{
    HAL_StatusTypeDef status;

    I2cDriverData_t *i2cData = (I2cDriverData_t *)(dev->driverData);
    I2cConfig_t *i2cConfig = (I2cConfig_t *)(dev->driverConfig);

    status = HAL_I2C_Master_Transmit(i2cData->i2cHandle, address, p_data, length, i2cData->timeoutMs);
    
    if (status == HAL_OK)
    {
        return I2C_OK;
    }
    else if (status == HAL_BUSY)
    {

        LOG_WARN("I2C tx busy\n");
        return I2C_BUSY;
    }
    else
    {
        LOG_ERROR("I2C tx err: %d\n", status);
        return I2C_ERR_TX;
    }
}

I2cResult_t stm32_i2c_read(Device_t* dev,uint8_t address, uint8_t *p_data, size_t length)
{
    HAL_StatusTypeDef status;

    I2cDriverData_t *i2cData = (I2cDriverData_t *)(dev->driverData);
    I2cConfig_t *i2cConfig = (I2cConfig_t *)(dev->driverConfig);

    status = HAL_I2C_Master_Receive(i2cData->i2cHandle, address, p_data, length, i2cData->timeoutMs);
    
    if (status == HAL_OK)
    {
        return I2C_OK;
    }
    else if (status == HAL_BUSY)
    {

        LOG_WARN("I2C tx busy\n");
        return I2C_BUSY;
    }
    else
    {
        LOG_ERROR("I2C tx err: %d\n", status);
        return I2C_ERR_TX;
    }
}
