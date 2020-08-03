#ifndef MESSAGE_ID_H_
#define MESSAGE_ID_H_

typedef enum MessageId
{
    ID_ERROR,
    ID_SPEED_CMD,
    ID_BASIC_TELEMETRY,
    ID_MANUAL_CMDS,
    ID_LOG,

    ID_MAX // Last ID
} MessageId;

#endif