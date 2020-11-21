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


void car_task( void * pvParameters)
{
    car_init();
   
    StateData_t stateData;  
    
    

    while(1)
    {
        LOG_DEBUG("Car task\r\n");       
        stateData = pop_state_data();        
        LOG_DEBUG("New car state data: event = %d, data = %d\n", stateData.event, stateData.data);
        run_state(&stateData);

    }
}