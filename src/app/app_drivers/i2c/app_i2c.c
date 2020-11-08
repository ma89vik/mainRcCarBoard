#include "app_i2c.h"
#include "i2c.h"
#include <stdint.h>
#include "log.h"
#include "error_def.h"

#include "FreeRTOS.h"


void app_i2c_init(app_i2c_handle_t* handle, I2C_HandleTypeDef *i2c_hal_handle)
{  
    handle->i2c_hal_handle = i2c_hal_handle;   
}

err_def_t app_i2c_read_reg(app_i2c_handle_t* handle, uint8_t dev_address, uint16_t reg_address, uint8_t *data, size_t len, uint32_t timeout)
{
    uint8_t ret = HAL_I2C_Mem_Read(handle->i2c_hal_handle, dev_address << 1,  reg_address, 1, data, len, timeout);

    if (ret != HAL_OK){
        LOG_ERROR("I2C HAL error: %d\n", ret);
        return ERR_I2C_HW;
    } else {
        return ERR_OK;
    }

}

err_def_t app_i2c_write_reg(app_i2c_handle_t* handle, uint8_t dev_address, uint16_t reg_address, uint8_t *data, size_t len, uint32_t timeout)
{
    uint8_t ret = HAL_I2C_Mem_Write(handle->i2c_hal_handle, dev_address << 1,  reg_address, 1, data, len, timeout);

    if (ret != HAL_OK){
        LOG_ERROR("I2C HAL error: %d\n", ret);
        return ERR_I2C_HW;
    } else {
        return ERR_OK;
    }
}