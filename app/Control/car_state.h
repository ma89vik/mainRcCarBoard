#ifndef CAR_STATE_H_
#define CAR_STATE_H_

#include "stdio.h"

#define NUM_STATES 5

typedef enum 
{
    INIT = 0,
    IDLE = 1,
    ARM = 2,
    AUTO = 3,
    MANUAL = 4,
} CarState_t;

typedef enum
{
    SET_SPEED_EVT = 0,
    SET_STEERING_EVT,
    SET_BASIC_CMD_EVT,
    SET_STATE_EVT,
}CarEvent_t;



typedef struct StateData
{
    CarEvent_t event;
    int16_t data;
}StateData_t;

void run_state(StateData_t *data);
volatile CarState_t get_car_state();

#endif