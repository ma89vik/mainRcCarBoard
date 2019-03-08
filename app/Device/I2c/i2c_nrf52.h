#ifndef I2C_NRF52_H_
#define I2C_NRF52_H_

#include "device.h"
#include "i2c_device.h"

#include <stddef.h>
#include <stdint.h>

typedef struct Nrf52I2cDriverData
{
} I2cDriverData_t;

I2cResult_t nrf52_i2c_init(Device_t *dev);
I2cResult_t nrf52_i2c_write(uint8_t address, uint8_t *p_data, size_t length);
I2cResult_t nrf52_i2c_read(uint8_t address, uint8_t *p_data, size_t length);

#endif