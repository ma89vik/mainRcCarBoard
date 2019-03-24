#include "observer.h"

#include "imu_handler.h"
#include "gps_handler.h"
#include "FreeRTOS.h"
#include "task.h"
#include "log.h"


bool observer_init()
{
    //imu_init();
    gps_init();
}


void v_observer_task(void *pvParameters)
{
    observer_init();

    portTickType xLastExecutionTime;
    volatile unsigned portBASE_TYPE uxLine = 0;

    float heading;  
   
    while(1)
    {
        xLastExecutionTime = xTaskGetTickCount();
        
        LOG_DEBUG("Obs");

        //Read latest sensor data from IMU and GPS
        //heading = read_compass_heading();
        //myPrintf(heading, result);
        
        gps_update();


        vTaskDelayUntil( &xLastExecutionTime, 1000 );
    }

}


ObserverData_t get_observer_data()
{
    //Need mutex
    
}