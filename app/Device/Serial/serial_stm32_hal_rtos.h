#ifndef SERIAL_STM32_HAL_RTOS_H_
#define SERIAL_STM32_HAL_RTOS_H_

#include "device.h"
#include "ring_buffer.h"
#include "serial_device.h"

#include "usart.h"

typedef struct Stm32HalRtosSerialDriverData
{
    UART_HandleTypeDef *uartHandle;
    RingBuffer_t inbox;
} SerialDriverData_t;

SerialResult_t stm32_hal_rtos_serial_init(Device_t *dev);
SerialResult_t stm32_hal_rtos_serial_write(Device_t *dev, uint8_t bytes, uint16_t len);
int16_t stm32_hal_rtos_serial_read(Device_t *dev, uint8_t *result);

#endif