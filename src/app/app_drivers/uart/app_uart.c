#include "app_uart.h"
#include "usart.h"
#include "ring_buffer.h"
#include "string.h"
#include "led.h"

#define NUM_SERIAL 1

//Needed for converting from handle to device when we get HAL interrupt
static int serialIndex = 0;
static UART_HandleTypeDef* uartHandle[NUM_SERIAL] = {0};
static app_uart_handle_t* app_uart_handle[NUM_SERIAL] = {0};
static uint8_t handleToIndex(UART_HandleTypeDef* huart);


app_uart_err_t app_uart_init(app_uart_handle_t *dev)
{
    if (!dev)
    {
        return SERIAL_ERR_INSTANCE;
    }
    uint32_t err_code;

    uartHandle[serialIndex] = dev->uartHandle;
    app_uart_handle[serialIndex] = dev;
    serialIndex++;

    ring_buffer_init(&(dev->inbox), dev->buffer, 512);

    //Init DMA
    HAL_UART_Receive_DMA(dev->uartHandle, &(dev->rxData), 1);
    dev->txReady = true;
    

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    uint8_t idx = handleToIndex(huart);

    ring_buffer_put( &(app_uart_handle[idx]->inbox), app_uart_handle[idx]->rxData );

}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart)
{
    led_set(LED_BLUE, 1);
    uint8_t idx = handleToIndex(huart);
    app_uart_handle[idx]->txReady = true;
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    int a = 2;
    //__HAL_UART_CLEAR_FLAG(huart, UART_CLEAR_PEF);
	//__HAL_UART_CLEAR_FLAG(huart, USART_ICR_FECF);
	//__HAL_UART_CLEAR_FLAG(huart, USART_ICR_ORECF);
}

app_uart_err_t app_uart_write(app_uart_handle_t *dev, uint8_t *bytes, uint16_t len)
{

    if(dev->txReady)
    {
        dev->txReady = false;
        memcpy(dev->outbox, bytes, len);
        HAL_UART_Transmit_DMA(dev->uartHandle, dev->outbox, len);

        return SERIAL_OK;
    }
    else
    {
        return SERIAL_WRITE_ERR;
    }   

}
app_uart_err_t app_uart_read(app_uart_handle_t *dev, uint8_t *result)
{
    
}

app_uart_err_t app_uart_read_byte(app_uart_handle_t *dev, uint8_t *result)
{
    
    int8_t err = ring_buffer_get(&dev->inbox, result);
    
    
    if (err == 0)
    {
        return SERIAL_OK;
    }
    else
    {
        return SERIAL_READ_ERR;
    }
}


uint8_t handleToIndex(UART_HandleTypeDef* huart)
{
    for(int i = 0; i<NUM_SERIAL;i++)
    {
        if(uartHandle[i] == huart)
        {
            return i;
        }
    }
}