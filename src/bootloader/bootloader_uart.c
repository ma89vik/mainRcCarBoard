#include "bootloader_uart.h"
#include "usart.h"
#include "string.h"
#include "led.h"



void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart)
{
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
}

err_def_t bootloader_uart_write(uart_handle_t *dev, uint8_t *bytes, uint16_t len)
{
    HAL_UART_Transmit(dev->uartHandle, bytes, len, HAL_MAX_DELAY);

    return ERR_OK;
}