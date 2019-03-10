#ifndef PWM_H
#define PWM_H

#include <stdint.h>

void pwm_init();
void pwm_set_pulse(uint16_t ch0, uint16_t ch1);
void pwm_set_pulse_motor(uint16_t ch0);
void pwm_set_pulse_steering(uint16_t ch1);


#endif