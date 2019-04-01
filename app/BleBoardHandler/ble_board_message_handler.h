#ifndef BLE_BOARD_MESSAGES_H_
#define BLE_BOARD_MESSAGES_H_

#include "message_parser.h"

void ble_board_msg_handler_init();
void ble_board_handle_msg(Msg_t *msg);


#endif