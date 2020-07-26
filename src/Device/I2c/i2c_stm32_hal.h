#ifndef I2C_STM32_H_
#define I2C_STM32_H_

#include "device.h"
#include "i2c_device.h"

#include "i2c.h"

#include <stddef.h>
#include <stdint.h>

typedef struct Stm32I2cDriverData
{
    I2C_HandleTypeDef *i2cHandle;
     uint16_t timeoutMs;
} I2cDriverData_t;

I2cResult_t stm32_i2c_init(Device_t *dev);
I2cResult_t stm32_i2c_write(Device_t* dev,uint8_t address, uint8_t *p_data, size_t length);
I2cResult_t stm32_i2c_read(Device_t* dev,uint8_t address, uint8_t *p_data, size_t length);

#endif