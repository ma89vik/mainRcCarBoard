#include "bootloader_uart.h"
#include "usart.h"
//#include "ring_buffer.h"
#include "string.h"
#include "led.h"



app_uart_err_t app_uart_init(app_uart_handle_t *dev)
{

    

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart)
{
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
}

app_uart_err_t app_uart_write(app_uart_handle_t *dev, uint8_t *bytes, uint16_t len)
{

}
app_uart_err_t app_uart_read(app_uart_handle_t *dev, uint8_t *result)
{
    
}

app_uart_err_t app_uart_read_byte(app_uart_handle_t *dev, uint8_t *result)
{
}
