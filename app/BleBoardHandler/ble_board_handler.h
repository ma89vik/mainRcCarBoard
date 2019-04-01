#ifndef BLE_BOARD_HANDLER_H_
#define BLE_BOARD_HANDLER_H_

#include <stdint.h>

void v_ble_board_handler_task(void *vParameters);
void ble_board_handler_set_speed(int16_t speedCmd);
void ble_board_handler_set_steering(int16_t steeringCmd);
#endif