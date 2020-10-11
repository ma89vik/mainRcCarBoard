#pragma once

#include "ring_buffer.h"
#include "stm32f4xx_hal.h"
#include "error_def.h"

typedef struct
{
    UART_HandleTypeDef *uartHandle;
    uint8_t buffer[512];
    RingBuffer_t inbox;
    uint8_t outbox[256];
    volatile bool txReady;
    uint8_t rxData;
} app_uart_handle_t;


err_def_t app_uart_init(app_uart_handle_t *dev, UART_HandleTypeDef *uartHandle);
err_def_t app_uart_write(app_uart_handle_t *dev, uint8_t *bytes, uint16_t len);
err_def_t app_uart_read(app_uart_handle_t *dev, uint8_t *result);
err_def_t app_uart_byte(app_uart_handle_t *dev, uint8_t *result);

