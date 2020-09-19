#include "app_loader.h"
#include "bootloader_uart.h"
#include "memory_map.h"
#include "board.h"
#include "stdio.h"
#include <stdlib.h>


static void load_app(uint32_t pc, uint32_t sp) {
    __asm("           \n\
          cpsid if    /* disable interruprs */\n\
          msr msp, r1 /* load r1 into MSP */\n\
          bx r0       /* branch to the address at r0 */\n\
    ");
}

void app_loader_start()
{
    /* Verify app */   
    
    uint32_t *app_code = (uint32_t *)&__approm_start__;
    uint32_t app_sp = app_code[0];
    uint32_t app_start = app_code[1];

    char buf[100];
    sprintf(buf, "Loading app from 0x%p: sp = 0x%lX, start = 0x%lX\n",app_code , app_sp, app_start);
    bootloader_uart_write(&log_uart, buf, 0);

    /* De-init all HW */
    load_app(app_start, app_sp);

    /* Should never get here */
    abort();
}