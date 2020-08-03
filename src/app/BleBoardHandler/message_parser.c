#include "message_parser.h"
#include "crc.h"
#include "cobs.h"
#include "ring_buffer.h"
#include "linear_buffer.h"
#include "log.h"


#include "string.h"

#define PACKET_LEN_IDX 0
#define PACKET_ID_IDX 1
#define PACKET_CRC_IDX 2

//1 byte len + 1 byte id + 2 byte CRC
#define PACKET_PAYLOAD_IDX 4

static MsgParseResult_t find_delimiter(MsgParser_t *msgParser);

void msg_parser_init(MsgParser_t *msgParser, char* inboxBuf, uint16_t inbox_n_elem)
{
    ring_buffer_init(&msgParser->inbox, inboxBuf, inbox_n_elem);
    msgParser->msgBuf = linear_buf_init(msgParser->msgBufStorage, RAW_DATA_MAX_LENGTH);

    crcInit();
}

bool msg_add_byte(MsgParser_t *msgParser, uint8_t byte)
{
    ring_buffer_put(&msgParser->inbox, byte);
}

MsgParseResult_t parse_packet(MsgParser_t *msgParser, Msg_t * parsedMsg)
{
    MsgParseResult_t status = find_delimiter(msgParser);
  
    if(status == DELIMITER_FOUND)
    {
        uint8_t msgStream[RAW_DATA_MAX_LENGTH];

        uint8_t packetLen = msgParser->msgBuf.bytesWritten;

        cobs_decode(msgParser->msgBuf.buffer,  packetLen, msgStream);

        linear_buf_clear(&msgParser->msgBuf);

        uint8_t payloadLen = msgStream[PACKET_LEN_IDX];
        uint8_t payloadId = msgStream[PACKET_ID_IDX];
        
        crc payloadCrc; 
        memcpy(&payloadCrc, &msgStream[PACKET_CRC_IDX] , 2);

        crc calculatedCrc = crcFast(&msgStream[PACKET_PAYLOAD_IDX],payloadLen);


        if(payloadCrc != calculatedCrc)
        {
            LOG_WARN("CRC err\n");
            return CRC_ERR;

        }
        else
        {
            LOG_DEBUG("CRC OK\n");
            parsedMsg->msgId = payloadId;
            parsedMsg->length = payloadLen;
            memcpy(parsedMsg->payload, &msgStream[PACKET_PAYLOAD_IDX], payloadLen);

            return OK;
        }
    }

    else
    {
        return IN_PROGRESS;
    }   


}



static MsgParseResult_t find_delimiter(MsgParser_t *msgParser)
{
    uint16_t bytesToRead = ring_buffer_length(&msgParser->inbox);

    uint8_t byteRead;
    

    for(int i = 0; i<bytesToRead; i++)
    {
        ring_buffer_get(&msgParser->inbox, &byteRead);
        bool linBufStatus = linear_buf_push(&msgParser->msgBuf, byteRead);

        if(linBufStatus == false)
        {
            //No delimiter found before max message length
            linear_buf_clear(&msgParser->msgBuf);
            LOG_WARN("Corrupted message, no delim\n");

            return NO_DELIMITER;
        }  

        if(byteRead == DELIMITER)
        {
            return DELIMITER_FOUND;
        }      

    }
    return IN_PROGRESS;
} 

bool compose_packet(MsgParser_t *msgParser, Msg_t *msg)
{
    uint8_t msgStream[RAW_DATA_MAX_LENGTH];

    if(msg->length > PAYLOAD_MAX_LENGTH)
    {
        //Invalid message length
        return false;
    }

    // + 2 for end of packet padding and cobs byte
    uint8_t packetLen = msg->length + PACKET_PAYLOAD_IDX + 2;


    msgStream[PACKET_LEN_IDX] = msg->length;
    msgStream[PACKET_ID_IDX] = msg->msgId;

    crc payloadCrc = crcFast(msg->payload, msg->length);
    
    memcpy(&msgStream[PACKET_CRC_IDX], &payloadCrc, 2);
    

    //msgStream[]   
    memcpy(&msgStream[PACKET_PAYLOAD_IDX], msg->payload, msg->length);
    
    //Pad using Consistant overhead byte stuffing    
    cobs_encode(msgStream, packetLen -1, msgParser->outbox.data);

    msgParser->outbox.data[packetLen - 1] = DELIMITER;
    msgParser->outbox.length = packetLen;
  
    return true;  
}


