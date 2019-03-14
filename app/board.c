#include "board.h"
#include "serial_stm32_hal_rtos.h"
#include "i2c_stm32_hal.h"

static SerialConfig_t serialConfigGps = {
    .init = stm32_hal_rtos_serial_init,
};

static SerialDriverData_t serialDriverDataGps = {
    .uartHandle = &huart3, 
};

Device_t deviceGps = {
    .driverConfig = &serialConfigGps,
    .driverData = &serialDriverDataGps,
};

// I2C bus for IMU
static I2cConfig_t i2cConfig = {
    .init = stm32_i2c_init,
};

static I2cDriverData_t i2cDriverData = {
    .i2cHandle = &hi2c1,
    .timeoutMs = 100,
};

Device_t deviceI2c = {
    .driverConfig = &i2cConfig,
    .driverData = &i2cDriverData,
};