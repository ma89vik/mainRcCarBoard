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

void myPrintf(float fVal, char* result)
{
    
    int dVal, dec, i;

    fVal += 0.005;   // added after a comment from Matt McNabb, see below.

    dVal = fVal;
    dec = (int)(fVal * 100) % 100;

    memset(result, 0, 100);
    result[0] = (dec % 10) + '0';
    result[1] = (dec / 10) + '0';
    result[2] = '.';

    i = 3;
    while (dVal > 0)
    {
        result[i] = (dVal % 10) + '0';
        dVal /= 10;
        i++;
    }

    
}

v_observer_task(void *pvParameters)
{
    observer_init();

    portTickType xLastExecutionTime;
    volatile unsigned portBASE_TYPE uxLine = 0;

    float heading;  
    char result[100];
    while(1)
    {
        xLastExecutionTime = xTaskGetTickCount();

        //Read latest sensor data from IMU and GPS
        //heading = read_compass_heading();
        //myPrintf(heading, result);
        //LOG_DEBUG("test\n");
        gps_update();
        vTaskDelayUntil( &xLastExecutionTime, 500 );
    }

}


ObserverData_t get_observer_data()
{
    //Need mutex
    
}