#ifndef DEVICE_H
#define DEVICE_H

typedef struct DEVICE_H
{
    void *driverData;
    const void *driverApi;
    const void *driverConfig;
} Device_t;

#endif