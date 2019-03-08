#include "board.h"
#include "serial_stm32_hal_rtos.h"

static SerialConfig_t serialConfigGps = {
    .init = stm32_hal_rtos_serial_init,
};

static SerialDriverData_t serialDriverDataGps = {

};

Device_t deviceGps = {
    .driverConfig = &serialConfigGps,
    .driverData = &serialDriverDataGps,
};

// I2C bus for OpenMV and IMU
/*static I2cConfig_t i2cConfig = {
    .init = nrf52_i2c_init,
};

static I2cDriverData_t i2cDriverData;

Device_t deviceI2c = {
    .driverConfig = &i2cConfig,
    .driverData = &i2cDriverData,
};*/