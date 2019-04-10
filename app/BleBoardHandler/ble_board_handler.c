#include "FreeRTOS.h"
#include "task.h"
#include "ble_board_handler.h"
#include "ble_board_message_handler.h"
#include "message_parser.h"
#include "message_id.h"
#include "pb_common.h"
#include "pb_encode.h"
#include "cmds.pb.h"
#include "telemetry.pb.h"
#include "board.h"
#include "serial_device.h"
#include "log.h"
#include "car_state.h"


#define INBOX_SIZE 1024
#define TELEMETRY_MSG_PERIOD_MS 500

static MsgParser_t msgParser;
char inboxBuf[INBOX_SIZE];
static Msg_t msgIn;
static Msg_t msgOut;

static bool handle_msg();
static void ble_board_init();
static void ble_board_handler_send_msg(const void * protobufMsgStruct, const pb_field_t msgFields[]);

static send_telemetry();

void v_ble_board_handler_task(void *vParameters)
{
    portTickType xLastExecutionTime, xLastTelemetryMsg, xTelemetryMsgPeriod;
    
    xLastExecutionTime = xTaskGetTickCount();
    xLastTelemetryMsg = 0;
    xTelemetryMsgPeriod = TELEMETRY_MSG_PERIOD_MS/portTICK_PERIOD_MS;

    ble_board_init();  
    
    while(1)
    {
        xLastExecutionTime = xTaskGetTickCount();
        handle_msg();
        
        if((xLastExecutionTime - xLastTelemetryMsg) >= xTelemetryMsgPeriod)
        {
            xLastTelemetryMsg = xLastExecutionTime;
            send_telemetry();
        }
        
        vTaskDelayUntil( &xLastExecutionTime, 100 );

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
  

    //Serial read
    uint8_t byte;

    while (serial_read_byte(&deviceBleBoard, &byte) == SERIAL_OK)
    {
        msg_add_byte(&msgParser, byte);   
    }
 

    if(parse_packet(&msgParser, &msgIn) == OK)
    {
        ble_board_handle_msg(&msgIn);

    
    }
    return 0;
}


static send_telemetry()
{
    BasicTelemetry basicTelemetryMsg = BasicTelemetry_init_default;

    basicTelemetryMsg.carState = get_car_state();

    msgOut.msgId = ID_BASIC_TELEMETRY;

    ble_board_handler_send_msg(&basicTelemetryMsg, BasicTelemetry_fields); 
}

void send_log()
{/*
    Log logMsg = Log_init_default;

    logMsg.logMsg = "Abcd\n";

    msgOut.msgId = ID_BASIC_TELEMETRY;

    ble_board_handler_send_msg(&basicTelemetryMsg, BasicTelemetry_fields); */
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