#include "car_interface.h"
#include "FreeRTOS.h"
#include "message_buffer.h"
#include "car_state.h"


static MessageBufferHandle_t xBleBoardCmdMsgBuf;
static const size_t xBleBoardCmdMsgBufSizeBytes = 20;

void car_interface_init()
{
    xBleBoardCmdMsgBuf = xMessageBufferCreate(xBleBoardCmdMsgBufSizeBytes);
}

void car_request_speed(int16_t speed)
{

}

void car_request_steering(int16_t steering)
{

}
 
void car_request_mode_change(CarState_t carState)
{
    StateData_t stateData;
    stateData.event = SET_STATE_EVT;
    stateData.data = (int16_t)carState;

    xMessageBufferSend(xBleBoardCmdMsgBuf, &stateData, sizeof(stateData), 0);
    
}

StateData_t pop_state_data()
{
    StateData_t newStateData;
    xMessageBufferReceive(xBleBoardCmdMsgBuf, &newStateData, sizeof(newStateData), portMAX_DELAY);

    return newStateData;
}