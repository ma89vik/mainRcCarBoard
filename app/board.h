#ifndef BOARD_H__
#define BOARD_H__

#include "serial_device.h"
#include "serial_stm32_hal_rtos.h"



#define SERVO_PWM_CH 30
#define MOTOR_PWM_CH 31

#define TWI_SCL_M 3 //!< Master SCL pin.
#define TWI_SDA_M 4 //!< Master SDA pin.

#define UART_RX_PIN 8
#define UART_TX_PIN 6
#define UART_CTS_PIN 7
#define UART_RTS_PIN 5

#define DIST_SENS_IN_PIN 12
#define DIST_SENS_OUT_PIN 11

// Hardware timers
#define DIST_SENS_TIMER_ID 0

extern Device_t deviceGps;
extern Device_t deviceI2c;

#endif