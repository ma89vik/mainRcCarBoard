#pragma once

#include "usart.h"
#include "error_def.h"
#include <stdint.h>

typedef struct
{
    UART_HandleTypeDef *uartHandle;
} uart_handle_t;


err_def_t app_uart_init(uart_handle_t *dev);
err_def_t bootloader_uart_write(uart_handle_t *dev, uint8_t *bytes, uint16_t len);

