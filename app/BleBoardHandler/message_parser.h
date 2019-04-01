#ifndef MESSAGE_PARSER_H_
#define MESSAGE_PARSER_H_

#include "ring_buffer.h"
#include "linear_buffer.h"
#include <stdint.h>
#include <stddef.h>

#define PAYLOAD_MAX_LENGTH 100

#define RAW_DATA_MAX_LENGTH (PAYLOAD_MAX_LENGTH + 5) //2xCRC 1xlen 1xId 1xCobs
#define DELIMITER 0x00

typedef struct RawMessage {
    uint8_t data[RAW_DATA_MAX_LENGTH];
    size_t length;
} RawMsg_t;

typedef struct MsgParser {
    RingBuffer_t inbox;
    LinearBuffer_t msgBuf;

    uint8_t msgBufStorage[RAW_DATA_MAX_LENGTH]; 
    RawMsg_t outbox;


} MsgParser_t;

typedef enum MsgParseResult {
    OK,
    IN_PROGRESS,
    INVALID_FORMAT,
    NO_DELIMITER,
    DELIMITER_FOUND,
    CRC_ERR,
} MsgParseResult_t;


typedef struct Message {
    uint8_t msgId;
    uint8_t payload[PAYLOAD_MAX_LENGTH];
    size_t length;
} Msg_t;

void msg_parser_init(MsgParser_t *msgParser, char* inboxBuf, uint16_t inbox_n_elem);
bool msg_add_byte(MsgParser_t *msgParser, uint8_t byte);
MsgParseResult_t parse_packet(MsgParser_t *msgParser, Msg_t * parsedMsg);
bool compose_packet(MsgParser_t *msgParser, Msg_t *msg);

#endif