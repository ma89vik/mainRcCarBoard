#ifndef BOARD_H__
#define BOARD_H__

#include "serial_device.h"
#include "serial_stm32_hal.h"

#include "main.h"



#define SERVO_PWM_CH TIM_CHANNEL_1 //PC6
#define MOTOR_PWM_CH TIM_CHANNEL_2 //PB5

#define TWI_SCL_M 3 //!< Master SCL pin.
#define TWI_SDA_M 4 //!< Master SDA pin.

#define UART_RX_PIN 8
#define UART_TX_PIN 6
#define UART_CTS_PIN 7
#define UART_RTS_PIN 5


#define DIST_SENS_IN_PIN Dist_Sensor_In_Pin
#define DIST_SENS_IN_PORT Dist_Sensor_In_GPIO_Port
#define DIST_SENS_OUT_PIN Dist_Sensor_Trig_Pin
#define DIST_SENS_OUT_PORT Dist_Sensor_Trig_GPIO_Port

// Hardware timers
#define DIST_SENS_TIMER_ID 0

// Number of USARTS used on the board
#define NUM_SERIAL 2

extern Device_t deviceGps;
extern Device_t deviceBleBoard;
extern Device_t deviceI2c;

#endif