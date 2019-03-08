#ifndef GPS_HANDLER_H_
#define GPS_HANDLER_H_

#include "device.h"

/**
 * @brief Initializes the GPS sensor and the underlying uart driver
 *
 */
void gps_init();
void gps_update();

#endif