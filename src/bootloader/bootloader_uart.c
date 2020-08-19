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

void bootloader_uart_init(uart_handle_t *dev, UART_HandleTypeDef *uartHandle )
{
    dev->uartHandle = uartHandle;
}

err_def_t bootloader_uart_write(uart_handle_t *dev, uint8_t *bytes, uint16_t len)
{
     led_set(LED_GREEN, 1);
    int ret = HAL_UART_Transmit(dev->uartHandle, bytes, len, HAL_MAX_DELAY);

     led_set(LED_BLUE, 1);
    return ERR_OK;
}