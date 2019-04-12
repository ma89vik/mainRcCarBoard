#include "distance_sensor.h"
#include "board.h"
#include "log.h"
#include "gpio.h"
#include "tim.h"

#include <stdbool.h>
#include <stdint.h>

#define PULSE_PERIOD_US 60000U               // Datasheet recommends 60ms + between measurements
#define PULSE_LEN_US 10U // Datasheet recommends 10us+

static TIM_HandleTypeDef * distSensTim = &htim4;


static volatile uint32_t pulse_len_us;


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if(htim = distSensTim)
    {
        pulse_len_us =  __HAL_TIM_GET_COUNTER(htim);
    }
}

void dist_sens_init()
{
  HAL_TIM_IC_Start_IT(distSensTim, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(distSensTim, TIM_CHANNEL_2);
  
}

static uint32_t us_to_distance(uint32_t us)
{
    return us / 58;
}

uint32_t get_dist_cm()
{
    return us_to_distance(pulse_len_us);
}