#include "serial_stm32_hal_rtos.h"
#include "board.h"
#include "device.h"
#include "serial_device.h"
#include "usart.h"


SerialApi_t stm32_hal_rtos_serial_api = {
    .serial_read_byte = stm32_hal_rtos_serial_read,
    .serial_write = stm32_hal_rtos_serial_write,
};



SerialResult_t stm32_hal_rtos_serial_init(Device_t *dev)
{
    if (!dev)
    {
        return SERIAL_ERR_INSTANCE;
    }
    uint32_t err_code;

    SerialDriverData_t *serData = (SerialDriverData_t *)(dev->driverData);
    SerialConfig_t *serConfig = (SerialConfig_t *)(dev->driverConfig);

    dev->driverApi = &stm32_hal_rtos_serial_api;

}
SerialResult_t stm32_hal_rtos_serial_write(Device_t *dev, uint8_t bytes, uint16_t len)
{
    // while (app_uart_put('a') != NRFX_SUCCESS);
    return 0;
}
int16_t stm32_hal_rtos_serial_read(Device_t *dev, uint8_t *result)
{
    if (1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}