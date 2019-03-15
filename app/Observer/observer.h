#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include "gps_handler.h"

typedef struct ObserverData {
    GpsLocation gpsLoc
    //Other position data

}ObserverData_t;

ObserverData_t get_observer_data();

v_observer_task(void *pvParameters);

#endif