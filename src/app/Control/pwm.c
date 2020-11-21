/**
 * Copyright 2020 Marius
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */



#include <stdio.h>
#include <string.h>
#include "tim.h"
#include "board.h"
#include "log.h"
#include "FreeRTOS.h"
#include "task.h"

#define PWM_TOP_50Hz 20000

#define MOTOR_PWM_CH   TIM_CHANNEL_1
#define SERVO_PWM_CH   TIM_CHANNEL_2

static TIM_HandleTypeDef * controlPwm = &htim3;



void pwm_set_pulse(uint16_t ch0, uint16_t ch1)
{

}

void pwm_set_pulse_motor(uint16_t ch0)
{
    TIM_OC_InitTypeDef sConfigOC;
    LOG_ERROR("set motor pulse %d\n", ch0);
    
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = ch0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    taskENTER_CRITICAL();
    HAL_TIM_PWM_ConfigChannel(controlPwm, &sConfigOC, MOTOR_PWM_CH);
    HAL_TIM_PWM_Start(controlPwm, MOTOR_PWM_CH); 
    taskEXIT_CRITICAL();
}

void pwm_set_pulse_steering(uint16_t ch0)
{
    TIM_OC_InitTypeDef sConfigOC;
    LOG_ERROR("set sttering pulse %d\n", ch0);
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = ch0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    taskENTER_CRITICAL();
    HAL_TIM_PWM_ConfigChannel(controlPwm, &sConfigOC, SERVO_PWM_CH);
    HAL_TIM_PWM_Start(controlPwm, SERVO_PWM_CH);
    taskEXIT_CRITICAL();
}