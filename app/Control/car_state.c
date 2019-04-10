#include "car_state.h"
#include "car_control.h"

#include "log.h"



static volatile CarState_t currentState = IDLE;

typedef CarState_t state_func_t(StateData_t *data);

typedef void transition_func_t(StateData_t *data);

static CarState_t do_state_init(StateData_t *data);
static CarState_t do_state_idle(StateData_t *data);
static CarState_t do_state_arm(StateData_t *data);
static CarState_t do_state_manual(StateData_t *data);
static CarState_t do_state_auto(StateData_t *data);

static state_func_t* const state_table[NUM_STATES] = 
{
    do_state_init, do_state_idle, do_state_arm,  do_state_auto, do_state_manual
};

static do_init_to_idle(StateData_t *data);
static do_idle_to_arm(StateData_t *data);
static do_arm_to_manual(StateData_t *data);
static do_arm_to_auto(StateData_t *data);
static do_auto_to_manual(StateData_t *data);
static do_manual_to_auto(StateData_t *data);


static transition_func_t * const transitionTable[NUM_STATES][NUM_STATES] = 
{
    {NULL, do_init_to_idle, NULL, NULL, NULL },
    {NULL, NULL, do_idle_to_arm, NULL, NULL },
    {NULL, NULL, NULL,  do_arm_to_auto, do_arm_to_manual},
    {NULL, NULL, NULL, NULL, do_auto_to_manual},
    {NULL, NULL, NULL,  do_manual_to_auto,  NULL}
};

void run_state(StateData_t *data)
{
    CarState_t newState = state_table[currentState](data);

    transition_func_t *transition = transitionTable[currentState][newState];

    if(transition != NULL)
    {
    transition(data);

    }
  currentState = newState;
    
}


static CarState_t do_state_init(StateData_t *data)
{
    return IDLE;
}

static CarState_t do_state_idle(StateData_t *data)
{
    //If arm cmd
    if(data->event == SET_STATE_EVT)
    {
        if((CarState_t)data->data == ARM)
        {
          return ARM;   
        }       
    }    
 
  return IDLE;
     

}

static CarState_t do_state_arm(StateData_t *data)
{
        
    if(data->event == SET_STATE_EVT)
    {
        CarState_t stateCmd = (CarState_t)data->data; 

        if(stateCmd == MANUAL)
        {
          return MANUAL;   
        }
        else if(stateCmd == AUTO)
        {
          return AUTO;   
        }
        else if(stateCmd == IDLE)
        {
          return IDLE;   
        }
    }

   
      return ARM;
    

}

static CarState_t do_state_manual(StateData_t *data)
{
  CarState_t stateCmd;
  int8_t setpoint;
    switch(data->event)
    {
      case SET_STATE_EVT:
        stateCmd = (CarState_t)data->data; 

        if(stateCmd == AUTO)
        {
          return AUTO;   
        }
        else if(stateCmd == IDLE)
        {
          return IDLE;   
        }

        break;

      case SET_SPEED_EVT:
        setpoint = (int8_t)data->data; 
        set_motor_setpoint_pct(setpoint);
        break;

      case SET_STEERING_EVT:
        setpoint = (int8_t)data->data; 
        set_steering_setpoint_pct(setpoint);
        break;
    }
    
    return MANUAL;
    
    
}

static CarState_t do_state_auto(StateData_t *data)
{
    if(data->event == SET_STATE_EVT)
    {
        CarState_t stateCmd = (CarState_t)data->data; 

        if(stateCmd == MANUAL)
        {
          return MANUAL;   
        }
  
        else if(stateCmd == IDLE)
        {
          return IDLE;   
        }
    }

    return AUTO;
    
}

static do_init_to_idle(StateData_t *data)
{
    
}

static do_idle_to_arm(StateData_t *data)
{
    arm();
}
static do_arm_to_manual(StateData_t *data)
{

}

static do_arm_to_auto(StateData_t *data)
{

}

static do_auto_to_manual(StateData_t *data)
{

}

static do_manual_to_auto(StateData_t *data)
{

}


volatile CarState_t get_car_state()
{
    return currentState;
}