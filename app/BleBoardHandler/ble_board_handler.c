#include "FreeRTOS.h"
#include "task.h"
#include "ble_board_handler.h"
#include "ble_board_message_handler.h"
#include "message_parser.h"
#include "message_id.h"
#include "pb_common.h"
#include "pb_encode.h"
#include "cmds.pb.h"
#include "board.h"
#include "serial_device.h"
#include "log.h"


#define INBOX_SIZE 1024

static MsgParser_t msgParser;
char inboxBuf[INBOX_SIZE];
static Msg_t msgIn;
static Msg_t msgOut;

static bool handle_msg();
static void ble_board_init();
static void ble_board_handler_send_msg(const void * protobufMsgStruct, const pb_field_t msgFields[]);

uint8_t dummySerial[1024];
uint8_t dummySerialNumB = 0;

void v_ble_board_handler_task(void *vParameters)
{
    portTickType xLastExecutionTime;
    xLastExecutionTime = xTaskGetTickCount();

    ble_board_init();
 
    ble_board_handler_set_steering(33);
    
    while(1)
    {
        xLastExecutionTime = xTaskGetTickCount();
        //handle_msg();
        
        
        vTaskDelayUntil( &xLastExecutionTime, 5000 );

    }

}

static void ble_board_init()
{
    serial_init(&deviceBleBoard);

    ble_board_msg_handler_init();
    msg_parser_init(&msgParser, inboxBuf, INBOX_SIZE);
}



static bool handle_msg()
{
    //Test messages


    //Serial read
    for(int i =0 ; i<dummySerialNumB; i++)
    {
        msg_add_byte(&msgParser, dummySerial[i]);   
    }
 

    if(parse_packet(&msgParser, &msgIn) == OK)
    {
        ble_board_handle_msg(&msgIn);

    
    }
    return 0;
}

void ble_board_handler_set_speed(int16_t speedCmd)
{
    SpeedCmd speedCmdMsg = SpeedCmd_init_default;

    speedCmdMsg.speedSetPoint = speedCmd;

    msgOut.msgId = ID_SPEED_CMD;

    ble_board_handler_send_msg(&speedCmdMsg, SpeedCmd_fields);
   
}

void ble_board_handler_set_steering(int16_t steeringCmd)
{
    SteeringCmd steeringCmdMsg = SteeringCmd_init_default;

    steeringCmdMsg.steeringSetPoint = steeringCmd;

    msgOut.msgId = ID_SPEED_CMD;

    ble_board_handler_send_msg(&steeringCmdMsg, SteeringCmd_fields);
   
}

static void ble_board_handler_send_msg(const void * protobufMsgStruct, const pb_field_t msgFields[])
{
     pb_ostream_t outStream = pb_ostream_from_buffer(msgOut.payload, PAYLOAD_MAX_LENGTH);

     bool status = pb_encode(&outStream, msgFields, protobufMsgStruct);

     if(!status)
     {
         LOG_WARN("PB encode failed\n");
     }

    msgOut.length = outStream.bytes_written;
    
    if(compose_packet(&msgParser,&msgOut))
    {       
        serial_write(&deviceBleBoard, msgParser.outbox.data, msgParser.outbox.length );
    }
   

    
}