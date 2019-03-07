#include "board.h"
#include "i2c_nrf52.h"
#include "serial_nrf52.h"

static SerialConfig_t serialConfigGps = {
    .baudrate = 9600,
    .stopbits = 0,
    .parity = false,
    .init = nrf52_serial_init,
};

static SerialDriverData_t serialDriverDataGps = {

};

Device_t deviceGps = {
    .driverConfig = &serialConfigGps,
    .driverData = &serialDriverDataGps,
};

// I2C bus for OpenMV and IMU
static I2cConfig_t i2cConfig = {
    .init = nrf52_i2c_init,
};

static I2cDriverData_t i2cDriverData;

Device_t deviceI2c = {
    .driverConfig = &i2cConfig,
    .driverData = &i2cDriverData,
};