#pragma once

#include <stdint.h>

void nav_board_handler_task(void *vParameters);
void nav_board_handler_set_speed(int16_t speedCmd);
void nav_board_handler_set_steering(int16_t steeringCmd);
