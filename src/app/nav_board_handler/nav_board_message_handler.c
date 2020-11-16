#include "nav_board_message_handler.h"
#include "message_parser.h"
#include "cmds.pb.h"
#include "pb_decode.h"
#include "pb_encode.h"
#include "message_id.h"
#include "log.h"
//#include "car_interface.h"



typedef void (*MsgHandler_t)(Msg_t *msgIn);

void nav_board_speed_cmd(Msg_t *msgIn);
void nav_board_steering_cmd(Msg_t *msgIn);
void nav_board_manual_cmds(Msg_t *msgIn);

static MsgHandler_t msgHandlers[ID_MAX] ; 

void nav_board_msg_handler_init()
{
    for(int i = 0; i<ID_MAX; i++)
    {
        msgHandlers[i] = NULL;
    }

    msgHandlers[ID_SPEED_CMD] = nav_board_speed_cmd;
    msgHandlers[ID_STEERING_CMD] = nav_board_steering_cmd;
    msgHandlers[ID_MANUAL_CMDS] = nav_board_manual_cmds;
}


void nav_board_handle_msg(Msg_t *msg)
{
    if(msg->msgId < ID_MAX)
    {
        if(msgHandlers[msg->msgId] != NULL)
        {
            msgHandlers[msg->msgId](msg);
        }
        else
        {
            LOG_ERROR("Unassigned BLE msg handle\n");
        }
        
    }
    else
    {
        LOG_WARN("Invalid BLE msg ID");
    }
    

}

void nav_board_speed_cmd(Msg_t *msgIn)
{
    SpeedCmd speedCmdMsg = SpeedCmd_init_zero;

    pb_istream_t inStream = pb_istream_from_buffer(msgIn->payload, PAYLOAD_MAX_LENGTH);
    
    bool status = pb_decode(&inStream, SpeedCmd_fields,&speedCmdMsg);

    LOG_DEBUG("From BLE board: set speed \n");

 
    //car_request_speed(speedCmdMsg.speedSetPoint);

}

void nav_board_steering_cmd(Msg_t *msgIn)
{
    SteeringCmd steering_cmd_msg = SteeringCmd_init_zero;

    pb_istream_t inStream = pb_istream_from_buffer(msgIn->payload, PAYLOAD_MAX_LENGTH);
    
    bool status = pb_decode(&inStream, SteeringCmd_fields, &steering_cmd_msg);

    LOG_DEBUG("From BLE board: set steering = %d \n", steering_cmd_msg.steeringSetPoint);

 
    //car_request_speed(speedCmdMsg.speedSetPoint);

}


void nav_board_manual_cmds(Msg_t *msgIn)
{
    ManualControlCmds manualControlCmdsMsg = ManualControlCmds_init_zero;

    pb_istream_t inStream = pb_istream_from_buffer(msgIn->payload, PAYLOAD_MAX_LENGTH);
    
    bool status = pb_decode(&inStream, ManualControlCmds_fields,&manualControlCmdsMsg);

    LOG_DEBUG("From BLE board: set manual controls \n");

    
    //car_request_speed((int16_t)manualControlCmdsMsg.speedSetPoint);
    //car_request_steering((int16_t)manualControlCmdsMsg.steeringSetPoint);
    //car_request_mode_change(manualControlCmdsMsg.setCarState);
}