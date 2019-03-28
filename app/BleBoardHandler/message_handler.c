
#include "crc.h"
#include "cobs.h"
#include "ring_buffer.h"
#include "linear_buffer.h"

#define MSG_MAX_LENGTH 100
#define DELIMITER 0x00

typedef struct MsgHandler {
    RingBuffer_t inbox;
    LinearBuffer_t msgBuf;

    uint8_t msgBufStorage[MSG_MAX_LENGTH]; 

} MsgHandler_t;

typedef enum MsgParseResult {
    OK,
    IN_PROGRESS,
    INVALID_FORMAT,
    NO_DELIMITER,
    DELIMITER_FOUND,
    UNPARSED_TYPE
} MsgParseResult_t;

typedef struct RawMessage {
    uint8_t* payload;
    size_t length;
} RawMsg_t;

typedef struct Message {
    uint8_t msgId;
    uint8_t* payload;
    size_t length;
} Msg_t;

void msg_handler_init(MsgHandler_t *msgHandler, char* inboxBuf, uint16_t inbox_n_elem)
{
    ring_buffer_init(&msgHandler->inbox, inboxBuf, inbox_n_elem);
    msgHandler->msgBuf = linear_buf_init(msgHandler->msgBufStorage, MSG_MAX_LENGTH);
}

bool msg_add_byte(MsgHandler_t *msgHandler, uint8_t byte)
{
    ring_buffer_put(&msgHandler->inbox, byte);
}

MsgParseResult_t parseMsg(MsgHandler_t *msgHandler, Msg_t * parsedMsg)
{
    MsgParseResult_t status = find_delimiter(msgHandler);

    if(status = DELIMITER_FOUND)
    {
        
    }

}



static MsgParseResult_t find_delimiter(MsgHandler_t *msgHandler)
{
    uint16_t bytesToRead = ring_buffer_length(&msgHandler->inbox);

    uint8_t byteRead;

    for(int i = 0; i<bytesToRead; i++)
    {
        ring_buffer_get(&msgHandler->inbox, &byteRead);

        if(byteRead == DELIMITER)
        {
            return DELIMITER_FOUND;
        }
        else
        {

        }
        
        bool linBufStatus = linear_buf_push(&msgHandler->msgBuf, byteRead);
        if(linBufStatus == false)
        {
            //No delimiter found before max message length
            return NO_DELIMITER;
        }
        else
        {
            return IN_PROGRESS;
        }
        


    }
} 