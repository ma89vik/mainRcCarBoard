#pragma once

#include "stm32f4xx_hal.h"
#include "error_def.h"

typedef struct
{
    I2C_HandleTypeDef *i2c_hal_handle;
} app_i2c_handle_t;

void app_i2c_init(app_i2c_handle_t* handle, I2C_HandleTypeDef *i2c_hal_handle);

err_def_t app_i2c_read_reg(app_i2c_handle_t* handle, uint8_t dev_address, uint16_t reg_address, uint8_t *data, size_t len, uint32_t timeout);

err_def_t app_i2c_write_reg(app_i2c_handle_t* handle, uint8_t dev_address, uint16_t reg_address, uint8_t *data, size_t len, uint32_t timeout);
