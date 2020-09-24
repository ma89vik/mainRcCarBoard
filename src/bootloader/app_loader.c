#include "app_loader.h"
#include "bootloader_uart.h"
#include "memory_map.h"
#include "board.h"
#include "fw_header.h"
#include "printf.h"


static void load_app(uint32_t pc, uint32_t sp) {
    __asm("           \n\
          cpsid if    /* disable interruprs */\n\
          msr msp, r1 /* load r1 into MSP */\n\
          bx r0       /* branch to the address at r0 */\n\
    ");
}

static void app_header_print(fw_hdr_t *app_header)
{
    printf("App header\n");
    printf("Magic number: %X\n", app_header->fw_magic);
    printf("Header version: %d\n", app_header->fw_hdr_version);
    printf("CRC: %d\n", app_header->crc);
    printf("Size: %d\n", app_header->data_size);
    printf("Type: %X\n", app_header->fw_type);
    printf("Version: %d.%d.%d\n", app_header->version_major, app_header->version_minor, app_header->version_patch);
    printf("Vector table: %X\n", app_header->vector_addr);


}

void app_loader_start()
{
    /* Verify app */   
    
    void *app_code = (void *)&__approm_start__;
    fw_hdr_t *app_header = (fw_hdr_t*)app_code;

    app_header_print(app_header);

    char buf[100];
    printf("Loading app from 0x%p\n",app_code );

    /* De-init all HW */
    //load_app(app_start, app_sp);

    /* Should never get here */
    abort();
}