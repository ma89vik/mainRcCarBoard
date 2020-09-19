#pragma once

#include "usart.h"
#include "error_def.h"
#include <stdint.h>

typedef struct
{
    UART_HandleTypeDef *uartHandle;
} uart_handle_t;


void bootloader_uart_init(uart_handle_t *dev,  UART_HandleTypeDef *uartHandle);

/*
 If len is 0 then the number of bytes sent is determined by calling strlen */
err_def_t bootloader_uart_write(uart_handle_t *dev, char *bytes, uint16_t len);

