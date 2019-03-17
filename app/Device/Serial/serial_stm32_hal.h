#ifndef SERIAL_STM32_HAL_H_
#define SERIAL_STM32_HAL_H_

#include "device.h"
#include "ring_buffer.h"
#include "serial_device.h"

#include "usart.h"

typedef struct Stm32HalSerialDriverData
{
    UART_HandleTypeDef *uartHandle;
    uint8_t buffer[512];
    RingBuffer_t inbox;
    uint8_t rxData;
} SerialDriverData_t;

SerialResult_t stm32_hal_serial_init(Device_t *dev);
SerialResult_t stm32_hal_serial_write(Device_t *dev, uint8_t bytes, uint16_t len);
SerialResult_t stm32_hal_serial_read(Device_t *dev, uint8_t *result);
SerialResult_t stm32_hal_serial_read_byte(Device_t *dev, uint8_t *result);

#endif