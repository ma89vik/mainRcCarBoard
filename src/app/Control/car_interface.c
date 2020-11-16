#include "car_interface.h"
#include "FreeRTOS.h"
#include "message_buffer.h"
#include "car_state.h"

static StaticMessageBuffer_t car_interface_msg_buf_storage;
static MessageBufferHandle_t car_interface_msg_buf_handle;

#define CAR_INTERFACE_MSG_BUF_SIZE 40
static uint8_t car_interface_msg_buf[CAR_INTERFACE_MSG_BUF_SIZE];

void car_interface_init()
{
    car_interface_msg_buf_handle = xMessageBufferCreateStatic(sizeof(car_interface_msg_buf), car_interface_msg_buf, &car_interface_msg_buf_storage);
}

void car_request_speed(int16_t speed)
{
    StateData_t stateData;
    stateData.event = SET_SPEED_EVT;
    stateData.data = speed;

    xMessageBufferSend(car_interface_msg_buf_handle, &stateData, sizeof(stateData), 0);
}

void car_request_steering(int16_t steering)
{
    StateData_t stateData;
    stateData.event = SET_STEERING_EVT;
    stateData.data = (int16_t)steering;

    xMessageBufferSend(car_interface_msg_buf_handle, &stateData, sizeof(stateData), 0);

}
 
void car_request_mode_change(CarState_t carState)
{
    StateData_t stateData;
    stateData.event = SET_STATE_EVT;
    stateData.data = (int16_t)carState;

    xMessageBufferSend(car_interface_msg_buf_handle, &stateData, sizeof(stateData), 0);
    
}

StateData_t pop_state_data()
{
    StateData_t newStateData;
    xMessageBufferReceive(car_interface_msg_buf_handle, &newStateData, sizeof(newStateData), portMAX_DELAY);

    return newStateData;
}