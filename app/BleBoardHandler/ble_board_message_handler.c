#include "ble_board_message_handler.h"
#include "message_parser.h"
#include "cmds.pb.h"
#include "pb_decode.h"
#include "pb_encode.h"
#include "message_id.h"

#include "stdio.h"

typedef void (*MsgHandler_t)(Msg_t *msgIn);

void ble_board_speed_cmd(Msg_t *msgIn);

static MsgHandler_t msgHandlers[ID_MAX] ; 

void ble_board_msg_handler_init()
{
    for(int i = 0; i<ID_MAX; i++)
    {
        msgHandlers[i] = NULL;
    }

    msgHandlers[ID_SPEED_CMD] = ble_board_speed_cmd;
}


void ble_board_handle_msg(Msg_t *msg)
{
    if(msg->msgId < ID_MAX)
    {
        if(msgHandlers[msg->msgId] != NULL)
        {
            msgHandlers[msg->msgId](msg);
        }
        else
        {
            printf("Unassigned BLE msg handle\n");
        }
        
    }
    else
    {
        printf("Invalid BLE msg ID");
    }
    

}

void ble_board_speed_cmd(Msg_t *msgIn)
{
    SpeedCmd speedCmdMsg = SpeedCmd_init_zero;

    pb_istream_t inStream = pb_istream_from_buffer(msgIn->payload, PAYLOAD_MAX_LENGTH);
    
    bool status = pb_decode(&inStream, SpeedCmd_fields,&speedCmdMsg);

    printf("From BLE board: set speed = %d\n", speedCmdMsg.speedSetPoint);
}

void ble_board_steering_cmd(Msg_t *msgIn)
{
    SteeringCmd steeringCmdMsg = SteeringCmd_init_zero;

    pb_istream_t inStream = pb_istream_from_buffer(msgIn->payload, PAYLOAD_MAX_LENGTH);
    
    bool status = pb_decode(&inStream, SteeringCmd_fields,&steeringCmdMsg);

    printf("From BLE board: set steering = %d\n", steeringCmdMsg.steeringSetPoint);
}