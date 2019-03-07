#ifndef SERIAL_DEVICE_H_
#define SERIAL_DEVICE_H_

#include "device.h"
#include <stdbool.h>
#include <stdint.h>

typedef enum SerialResult
{
    SERIAL_NONE = -1,
    SERIAL_OK,
    SERIAL_ERR_INSTANCE,
    SERIAL_ERR_CONFIG,
} SerialResult_t;

typedef struct SerialConfig
{
    uint32_t baudrate;
    uint8_t stopbits;
    bool parity;
    SerialResult_t (*init)(Device_t *dev);

} SerialConfig_t;

typedef struct SerialApi
{
    int16_t (*serial_read_byte)(Device_t *dev, uint8_t *result);
    SerialResult_t (*serial_write)(Device_t *dev, uint8_t *bytes, uint16_t len);
} SerialApi_t;

static inline SerialResult_t serial_init(Device_t *dev)
{
    SerialConfig_t *cfg = (SerialConfig_t *)(dev->driverConfig);
    if (!cfg)
    {
        return SERIAL_ERR_CONFIG;
    }

    return cfg->init(dev);
}

static inline SerialResult_t serial_write(Device_t *dev, uint8_t *bytes,
                                          uint16_t len)
{
    if (!dev)
    {
        return SERIAL_ERR_INSTANCE;
    }

    SerialApi_t *api = (SerialApi_t *)(dev->driverApi);

    if (api->serial_write)
    {
        return api->serial_write(dev, bytes, len);
    }

    return SERIAL_ERR_INSTANCE;
}

static inline int16_t serial_read_byte(Device_t *dev, uint8_t *result)
{
    if (!dev)
    {
        return -1;
    }

    SerialApi_t *api;
    api = (SerialApi_t *)(dev->driverApi);

    if (api->serial_read_byte)
    {
        return api->serial_read_byte(dev, result);
    }

    return SERIAL_ERR_INSTANCE;
}

#endif