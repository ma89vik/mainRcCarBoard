#include "bootloader_main.h"
#include "bootloader_uart.h"
#include "usart.h"
#include "led.h"
#include "stm32f4xx_hal.h"
#include "gpio.h"



void bootloader_main()
{
    /*
    1. Check app
     */
    uart_handle_t uart;
    bootloader_uart_init(&uart, &huart2);

    while(1) {
        HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12 , 1);

        led_set(LED_BLUE, 1);
        for (int i=0; i< 1000; i++) {
            int a = 3 *i;
        }

        led_set(LED_GREEN, 1);
        bootloader_uart_write(&uart, "wpord", 10);


        for (int i=0; i< 100000; i++) {
            int a = 3 *i;
        }
        //bootloader_uart_write(&uart, "world", 6);
    }

    abort();
}

