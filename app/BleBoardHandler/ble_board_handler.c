#include "FreeRTOS.h"
#include "task.h"


void v_ble_board_handler_task(void *vParameters)
{

}


enum MsgParseResult {
    OK,
    IN_PROGRESS,
    INVALID_FORMAT,
    NO_DELIMITER,
    UNPARSED_TYPE
};

bool parseMsg(char *msg, )