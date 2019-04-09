#ifndef CAR_INTERFACE_H_
#define CAR_INTERFACE_H_

#include <stdint.h>

#include "car_state.h"

void car_request_speed(int16_t speed);
void car_request_steering(int16_t steering);
void car_request_mode_change(CarState_t carState);

StateData_t pop_state_data();

#endif