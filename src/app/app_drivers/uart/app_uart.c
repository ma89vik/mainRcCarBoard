/**
 * Copyright 2020 Marius
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */



#include "app_uart.h"
#include "usart.h"
#include "ring_buffer.h"
#include "string.h"
#include "led.h"
#include "board.h"
#include "error_def.h"

#define NUM_SERIAL 1

//Needed for converting from handle to device when we get HAL interrupt
static int serialIndex = 0;
static UART_HandleTypeDef* s_uartHandles[NUM_SERIAL] = {NULL};
static app_uart_handle_t* s_app_uart_handles[NUM_SERIAL] = {NULL};
static uint8_t handleToIndex(UART_HandleTypeDef* huart);


err_def_t app_uart_init(app_uart_handle_t *dev, UART_HandleTypeDef *uartHandle)
{
    if (!dev)
    {
        return ERR_INVALID_ARGS;
    }

    uint32_t err_code = 0;

    dev->uartHandle = uartHandle;
    s_uartHandles[serialIndex] = uartHandle;
    s_app_uart_handles[serialIndex] = dev;
    serialIndex++;

    //ring_buffer_init(&(dev->inbox), dev->buffer, 512);

    //Init DMA
    //HAL_UART_Receive_DMA(dev->uartHandle, &(dev->rxData), 1);
    dev->txReady = true;
    
    return err_code;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    uint8_t idx = handleToIndex(huart);

    //ring_buffer_put( &(app_uart_handle[idx]->inbox), app_uart_handle[idx]->rxData );

}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart)
{
    led_set(LED_RED, 1);
    uint8_t idx = handleToIndex(huart);
    s_app_uart_handles[idx]->txReady = true;
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    //__HAL_UART_CLEAR_FLAG(huart, UART_CLEAR_PEF);
	//__HAL_UART_CLEAR_FLAG(huart, USART_ICR_FECF);
	//__HAL_UART_CLEAR_FLAG(huart, USART_ICR_ORECF);
}

err_def_t app_uart_write(app_uart_handle_t *dev, uint8_t *bytes, uint16_t len)
{

    while(!dev->txReady) 
    {}


    size_t bytes_to_send = len > sizeof(dev->outbox) ? sizeof(dev->outbox) : len;

    dev->txReady = false;
    memcpy(dev->outbox, bytes, bytes_to_send);
        
    HAL_StatusTypeDef ret = HAL_UART_Transmit_DMA(dev->uartHandle, dev->outbox, len);

    if (ret == HAL_OK) {
        return ERR_OK;
    } else {
        return ERR_FAIL;
    }
}

err_def_t app_uart_read(app_uart_handle_t *dev, uint8_t *result)
{
    return ERR_OK;
}

err_def_t app_uart_read_byte(app_uart_handle_t *dev, uint8_t *result)
{
    
    int8_t err = ring_buffer_get(&dev->inbox, result);
    
    
    if (err == 0)
    {
        return ERR_OK;
    }
    else
    {
        return ERR_FAIL;
    }
}


uint8_t handleToIndex(UART_HandleTypeDef* huart)
{
    for(int i = 0; i<NUM_SERIAL;i++)
    {
        if(s_uartHandles[i] == huart)
        {
            return i;
        }
    }
    return 0;
}

