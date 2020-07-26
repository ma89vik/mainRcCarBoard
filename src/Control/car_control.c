#include "car_control.h"
#include "pwm.h"
#include "log.h"
#include "distance_sensor.h"

//Steering servo min and max pulse length
static int16_t const STEERING_SERVO_PULSE_MIN = 1000;
static int16_t const STEERING_SERVO_PULSE_MAX = 2000;

//Motor ESC min and max pulse length
static int16_t const MOTOR_ESC_PULSE_MIN = 1000;
static int16_t const MOTOR_ESC_PULSE_MAX = 2000;


/**
 * @brief  Initialize the car control, including servo and motor to a safe sate
 * @note   
 * @retval None
 */
void car_control_init()
{
    
  
}

/**
 * @brief Set the new desired steering setpoint
 * 
 * @param angle_sp desired angle in percentage (-100% to 100%)
 */
void set_steering_setpoint_pct(int8_t steering_sp_pct)
{
    //Throw away command if outside of range
    if( (steering_sp_pct < -100) || (steering_sp_pct > 100) )
    {
        return;
    }
    
    int16_t range = (STEERING_SERVO_PULSE_MAX - STEERING_SERVO_PULSE_MIN)/200;
    uint16_t pulse_length = range*steering_sp_pct + STEERING_SERVO_PULSE_MIN + 100*range;
    
    pwm_set_pulse_steering(pulse_length);

    return;
}

void set_motor_setpoint_pct(int8_t motor_sp_pct)
{
    //Throw away command if outside of range
    if( (motor_sp_pct < -100) || (motor_sp_pct > 100) )
    {
        return;
    }
    
    int16_t range = (MOTOR_ESC_PULSE_MAX - MOTOR_ESC_PULSE_MIN)/200;
    uint16_t pulse_length = range*motor_sp_pct + MOTOR_ESC_PULSE_MIN + 100*range;
    
    pwm_set_pulse_motor(pulse_length);

    return;
}


/**
 * @brief Set motor speed to 0
 * 
 */
void emergency_stop()
{
    set_motor_setpoint_pct(0);
}

void arm()
{
  pwm_init();
}
