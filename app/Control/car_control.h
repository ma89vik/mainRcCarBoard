
#ifndef CAR_CONTROL_H
#define CAR_CONTROL_H


#include <stdint.h>

void vCarControlTask( void * pvParameters);

/**
 * @brief  Initialize the car control, including servo and motor to a safe sate
 * @note   
 * @retval None
 */
void car_control_init();

/**
 * @brief Set the new desired steering setpoint
 * 
 * @param angle_sp desired angle in percentage (-100% to 100%)
 */
void set_steering_setpoint_pct(int8_t steering_sp_pct);

/**
 * @brief Set the new speed setpoint
 * 
 * @param speed_sp Desired speed in percentage, -100% to 100%
 */
void set_speed_setpoint(int8_t speed_sp_pct);

/**
 * @brief Set motor speed to 0
 * 
 */
void emergency_stop();

/**
 * @brief Event handler for Remote control car service
 * 
 */
//void on_rccs_evt(ble_rccs_evt_t * p_evt);


#endif