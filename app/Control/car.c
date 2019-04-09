#include "car.h"
#include "car_control.h"
#include "car_state.h"
#include "car_interface.h"

#include "log.h"

#include "FreeRTOS.h"
#include "task.h"
#include "message_buffer.h"



 
void car_init()
{
    car_interface_init();
    car_control_init();
   

  
}


void v_car_task( void * pvParameters)
{
    portTickType xLastExecutionTime;
    

     
    /// Initialise xLastExecutionTime so the first call to vTaskDelayUntil() works correctly
    xLastExecutionTime = xTaskGetTickCount();
    
    car_init();
   
    StateData_t stateData;
    
    
   
    

    while(1)
    {
        xLastExecutionTime = xTaskGetTickCount();
        LOG_DEBUG("Car task\r\n");

       
        stateData = pop_state_data();        
        run_state(&stateData);

        //vTaskDelayUntil( &xLastExecutionTime, 500 );
    }
}