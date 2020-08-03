#pragma once

#include "ring_buffer.h"
#include "usart.h"

typedef struct
{
    UART_HandleTypeDef *uartHandle;
    volatile uint8_t buffer[512];
    RingBuffer_t inbox;
    volatile uint8_t outbox[256];
    volatile bool txReady;
    uint8_t rxData;
} app_uart_handle_t;

typedef enum 
{
    SERIAL_NONE = -1,
    SERIAL_OK,
    SERIAL_ERR_INSTANCE,
    SERIAL_ERR_CONFIG,
    SERIAL_READ_ERR,
    SERIAL_WRITE_ERR,
} app_uart_err_t;

app_uart_err_t app_uart_init(app_uart_handle_t *dev);
app_uart_err_t app_uart_write(app_uart_handle_t *dev, uint8_t *bytes, uint16_t len);
app_uart_err_t app_uart_read(app_uart_handle_t *dev, uint8_t *result);
app_uart_err_t app_uart_byte(app_uart_handle_t *dev, uint8_t *result);
