#include <stdio.h>
#include <string.h>
#include "tim.h"
#include "board.h"
#include "log.h"

#define PWM_TOP_50Hz 20000

#define MOTOR_PWM_CH   TIM_CHANNEL_1
#define SERVO_PWM_CH   TIM_CHANNEL_2

static TIM_HandleTypeDef * controlPwm = &htim3;


void pwm_init()
{
     HAL_TIM_PWM_Start(controlPwm, SERVO_PWM_CH);
     HAL_TIM_PWM_Start(controlPwm, MOTOR_PWM_CH);
}


void pwm_set_pulse(uint16_t ch0, uint16_t ch1)
{

}

void pwm_set_pulse_motor(uint16_t ch0)
{
    TIM_OC_InitTypeDef sConfigOC;
  
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = ch0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(controlPwm, &sConfigOC, MOTOR_PWM_CH);
    HAL_TIM_PWM_Start(controlPwm, MOTOR_PWM_CH); 
}

void pwm_set_pulse_steering(uint16_t ch0)
{
    TIM_OC_InitTypeDef sConfigOC;
  
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = ch0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(controlPwm, &sConfigOC, SERVO_PWM_CH);
    HAL_TIM_PWM_Start(controlPwm, SERVO_PWM_CH); 
}