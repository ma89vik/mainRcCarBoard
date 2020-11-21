
#ifndef CAR_H
#define CAR_H


#include <stdint.h>

void car_task( void * pvParameters);

/**
 * @brief  Initialize the car control, including servo and motor to a safe sate
 * @note   
 * @retval None
 */
void car_init();



#endif