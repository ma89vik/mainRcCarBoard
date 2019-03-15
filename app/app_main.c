#include "app_main.h"

#include "FreeRTOS.h"
#include "task.h"

#include "gpio.h"

#include "serial_stm32_hal.h"
#include "car_control.h"


#define CAR_CONTROL_TASK_PRIORITY     ( tskIDLE_PRIORITY + 1 )



void app_main()
{
   
    xTaskCreate( vCarControlTask, (signed char*)"Car Control", configMINIMAL_STACK_SIZE, NULL, CAR_CONTROL_TASK_PRIORITY , NULL );
    
}