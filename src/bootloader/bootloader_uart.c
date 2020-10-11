#include "bootloader_uart.h"
#include "usart.h"
#include "string.h"
#include "led.h"
#include "board.h"


void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart)
{
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
}

void bootloader_uart_init(uart_handle_t *dev, UART_HandleTypeDef *uartHandle )
{
    dev->uartHandle = uartHandle;
}

err_def_t bootloader_uart_write(uart_handle_t *dev, char *bytes, uint16_t len)
{
    if (!dev) {
        return ERR_INVALID_ARGS;
    }

    int bytes_to_transfer = 0;
    if (len == 0) {
        bytes_to_transfer = strlen(bytes);
    } else {
        bytes_to_transfer = len;
    }

    HAL_UART_Transmit(dev->uartHandle, (uint8_t*)bytes, bytes_to_transfer, HAL_MAX_DELAY);

    return ERR_OK;
}

void _putchar(char byte)
{  
    HAL_UART_Transmit(log_uart.uartHandle,  (uint8_t*)&byte, 1, HAL_MAX_DELAY);
}
