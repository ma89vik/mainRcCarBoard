#include "app_main.h"


#include "gpio.h"
#include "app_uart.h"
#include "led.h"
#include "fw_header.h"
#include "usart.h"
#include "board.h"
#include "fault.h"
#include "log.h"

extern uint32_t _vector_table;

static const fw_hdr_t  __attribute__((section(".fw_hdr"), used)) FW_HEADER = {
    .fw_magic = FW_MAGIC_NUMBER,
    .fw_hdr_version = FW_HEADER_VERSION,
    .fw_type = FW_TYPE_APP,
    .version_major = 0,
    .version_minor = 1,
    .version_patch = 0,
    .vector_addr = (uint32_t)&_vector_table,
    .git_sha = GIT_SHA, //defined by cmake
};


void test(void *p)
{



    while(1) {

    }

}

int *a = 0;

void app_main_task()
{


    led_set(LED_BLUE, 1);


    log_config_t log_cfg = {
        .uart_handle = &huart2,
    };

    log_init(&log_cfg);
    app_uart_handle_t gps_uart_handle;
    app_uart_init(&gps_uart_handle, &huart3, true, false);  

    LOG_INFO("App started\n");

    fault_init();

    while(1)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        LOG_INFO("App tick\n");

    }
}