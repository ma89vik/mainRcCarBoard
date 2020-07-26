#ifndef _APP_MAIN_H_
#define _APP_MAIN_H_

#include "FreeRTOS.h"
#include "task.h"

void app_main();
void vApplicationStackOverflowHook( TaskHandle_t xTask,                                    signed char *pcTaskName );
#endif