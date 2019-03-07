#include "serial_nrf52.h"
#include "board.h"
#include "device.h"
#include "log.h"
#include "ring_buffer.h"
#include "serial_device.h"

#include "app_error.h"
#include "app_uart.h"
#include "bsp.h"
#include "nrf.h"
#include "nrf_delay.h"
#include "nrf_uarte.h"

#define UART_TX_BUF_SIZE 256 /**< UART TX buffer size. */
#define UART_RX_BUF_SIZE 256 /**< UART RX buffer size. */

SerialApi_t nrf52_serial_api = {
    .serial_read_byte = nrf52_serial_read,
    .serial_write = nrf52_serial_write,
};

void uart_error_handle(app_uart_evt_t *p_event)
{
    if (p_event->evt_type == APP_UART_COMMUNICATION_ERROR)
    {
        LOG_ERROR("Serial: com err");
        // APP_ERROR_HANDLER(p_event->data.error_communication);
    }
    else if (p_event->evt_type == APP_UART_FIFO_ERROR)
    {
        LOG_ERROR("Serial: fifo err");
        // APP_ERROR_HANDLER(p_event->data.error_code);
    }
}

SerialResult_t nrf52_serial_init(Device_t *dev)
{
    if (!dev)
    {
        return SERIAL_ERR_INSTANCE;
    }
    uint32_t err_code;

    SerialDriverData_t *serData = (SerialDriverData_t *)(dev->driverData);
    SerialConfig_t *serConfig = (SerialConfig_t *)(dev->driverConfig);

    dev->driverApi = &nrf52_serial_api;

    const app_uart_comm_params_t comm_params = {
        UART_RX_PIN, UART_TX_PIN, UART_RTS_PIN,           UART_CTS_PIN,
        0,           false,       NRF_UARTE_BAUDRATE_9600};

    APP_UART_FIFO_INIT(&comm_params, UART_RX_BUF_SIZE, UART_TX_BUF_SIZE,
                       uart_error_handle, APP_IRQ_PRIORITY_LOWEST, err_code);

    APP_ERROR_CHECK(err_code);
}
SerialResult_t nrf52_serial_write(Device_t *dev, uint8_t bytes, uint16_t len)
{
    // while (app_uart_put('a') != NRFX_SUCCESS);
    return 0;
}
int16_t nrf52_serial_read(Device_t *dev, uint8_t *result)
{
    if (app_uart_get(result) == NRF_SUCCESS)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}