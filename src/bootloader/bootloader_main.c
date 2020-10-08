#include "bootloader_main.h"
#include "bootloader_uart.h"
#include "usart.h"
#include "led.h"
#include "stm32f4xx_hal.h"
#include "gpio.h"
#include "app_loader.h"
#include "board.h"
#include "reset.h"
#include "printf.h"

void bootloader_main()
{
    /*
    1. Check app
     */

    bootloader_uart_init(&log_uart, &huart2);
    reset_print_and_clear_reason();
    printf("Bootloader started\n");
    app_loader_start();
}

