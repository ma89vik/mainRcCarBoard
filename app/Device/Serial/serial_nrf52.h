#ifndef SERIAL_NRF52382_H_
#define SERIAL_NRF52382_H_

#include "device.h"
#include "ring_buffer.h"
#include "serial_device.h"

typedef struct Nrf52SerialDriverData
{
    RingBuffer_t inbox;
    uint8_t rxPinNumber;
    uint8_t txPinNumber;
} SerialDriverData_t;

SerialResult_t nrf52_serial_init(Device_t *dev);
SerialResult_t nrf52_serial_write(Device_t *dev, uint8_t bytes, uint16_t len);
int16_t nrf52_serial_read(Device_t *dev, uint8_t *result);

#endif