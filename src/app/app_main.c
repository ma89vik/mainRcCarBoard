#include "app_main.h"

#include "FreeRTOS.h"
#include "task.h"

#include "gpio.h"
#include "app_uart.h"
/*
#include "serial_stm32_hal.h"
#include "car.h"
#include "observer.h"
#include "log.h"
#include "usb_log.h"
#include "ble_board_handler.h"

#define CAR_CONTROL_TASK_PRIORITY     ( tskIDLE_PRIORITY + 3 )
#define OBSERVER_TASK_PRIORITY     ( tskIDLE_PRIORITY + 2 )
#define LOG_TASK_PRIORITY     ( tskIDLE_PRIORITY + 1 )
#define BLE_BOARD_TASK_PRIORITY     ( tskIDLE_PRIORITY + 4 )*/



void app_main()
{

    app_uart_handle_t uart_handle;
    uart_handle.uartHandle = &huart3;
    app_uart_init(&uart_handle);


    while(1) {

        app_uart_write(&uart_handle, "hello world", 12);
    }
   /*LogConfig_t logConfig = {
       .init = usb_log_init,
   };

   
   log_init(&logConfig);


    xTaskCreate( v_car_task, (signed char*)"Car Control", 4*configMINIMAL_STACK_SIZE, NULL, CAR_CONTROL_TASK_PRIORITY , NULL );

    xTaskCreate( v_observer_task, (signed char*)"Observer", 8*configMINIMAL_STACK_SIZE, NULL, OBSERVER_TASK_PRIORITY , NULL );

    xTaskCreate( v_log_task, (signed char*)"Logger", 256, NULL, LOG_TASK_PRIORITY , NULL );
    
    xTaskCreate( v_ble_board_handler_task, (signed char*)"Ble handler", (uint16_t)4096, NULL, BLE_BOARD_TASK_PRIORITY , NULL );*/
}