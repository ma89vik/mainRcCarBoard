#ifndef GPS_HANDLER_H_
#define GPS_HANDLER_H_

#include "device.h"

#include <stdbool.h>
#include <stdint.h>

#define LOC_STR_MAX_LEN 15

typedef struct GpsLocations
{
    // Locations as integers for use in calculations
    uint16_t latDeg;
    uint16_t northMin;
    uint16_t northSec;
    uint16_t longDeg;
    uint16_t westMin;
    uint16_t westSec;

    // Location as strings
    char latitude[LOC_STR_MAX_LEN];
    char longitude[LOC_STR_MAX_LEN];

    bool valid;

} GpsLocation;

/**
 * @brief Initializes the GPS sensor
 *
 */
void gps_init();
void gps_update();

#endif