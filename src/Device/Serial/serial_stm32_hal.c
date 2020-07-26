#include "serial_stm32_hal.h"
#include "board.h"
#include "device.h"
#include "serial_device.h"
#include "usart.h"
#include "ring_buffer.h"
#include "log.h"
#include "string.h"

//Needed for converting from handle to device when we get HAL interrupt
static int serialIndex = 0;
static UART_HandleTypeDef* uartHandle[NUM_SERIAL] = {0};
static SerialDriverData_t* serialData[NUM_SERIAL] = {0};
static uint8_t handleToIndex(UART_HandleTypeDef* huart);

SerialApi_t stm32_hal_serial_api = {
    .serial_read_byte = stm32_hal_serial_read_byte,
    .serial_write = stm32_hal_serial_write,
};



SerialResult_t stm32_hal_serial_init(Device_t *dev)
{
    if (!dev)
    {
        return SERIAL_ERR_INSTANCE;
    }
    uint32_t err_code;

    SerialDriverData_t *serData = (SerialDriverData_t *)(dev->driverData);
    SerialConfig_t *serConfig = (SerialConfig_t *)(dev->driverConfig);

    dev->driverApi = &stm32_hal_serial_api;

    uartHandle[serialIndex] = serData->uartHandle;
    serialData[serialIndex] = serData;
    serialIndex++;

    ring_buffer_init(&(serData->inbox), serData->buffer, 512);

    //Init DMA
    HAL_UART_Receive_DMA(serData->uartHandle, &(serData->rxData), 1);
    serData->txReady = true;
    

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    uint8_t idx = handleToIndex(huart);

    ring_buffer_put( &(serialData[idx]->inbox), serialData[idx]->rxData );

}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart)
{
    uint8_t idx = handleToIndex(huart);
    serialData[idx]->txReady = true;
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    int a = 2;
    //__HAL_UART_CLEAR_FLAG(huart, UART_CLEAR_PEF);
	//__HAL_UART_CLEAR_FLAG(huart, USART_ICR_FECF);
	//__HAL_UART_CLEAR_FLAG(huart, USART_ICR_ORECF);
}

SerialResult_t stm32_hal_serial_write(Device_t *dev, uint8_t *bytes, uint16_t len)
{
   SerialDriverData_t *serData = (SerialDriverData_t *)(dev->driverData);
    if(serData->txReady)
    {
        serData->txReady = false;
        memcpy(serData->outbox, bytes, len);
        HAL_UART_Transmit_DMA(serData->uartHandle, serData->outbox, len);

        return SERIAL_OK;
    }
    else
    {
        return SERIAL_WRITE_ERR;
    }   

}
SerialResult_t stm32_hal_serial_read(Device_t *dev, uint8_t *result)
{
    SerialDriverData_t *serData = (SerialDriverData_t *)(dev->driverData);
    

}

SerialResult_t stm32_hal_serial_read_byte(Device_t *dev, uint8_t *result)
{
    SerialDriverData_t *serData = (SerialDriverData_t *)(dev->driverData);
    
    int8_t err = ring_buffer_get(&serData->inbox, result);
    

    
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