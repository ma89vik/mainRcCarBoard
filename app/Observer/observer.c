#include "observer.h"

#include "imu_handler.h"
#include "gps_handler.h"
#include "FreeRTOS.h"
#include "task.h"


bool observer_init()
{
    imu_init();
    gps_init();
}


v_observer_task(void *pvParameters)
{
    observer_init();

}


ObserverData_t get_observer_data()
{
    //Need mutex
    
}