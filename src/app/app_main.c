#include "app_main.h"


#include "gpio.h"
#include "app_uart.h"
#include "app_i2c.h"
#include "fxos8700.h"
#include "led.h"
#include "fw_header.h"
#include "usart.h"
#include "i2c.h"
#include "board.h"
#include "fault.h"
#include "log.h"
#include "nav_board_handler.h"
#include "car.h"

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


#define NAV_BOARD_TASK_STACK_SIZE 8096
#define NAV_BOARD_TASK_PRIORITY 6

#define CAR_TASK_STACK_SIZE 8096
#define CAR_TASK_PRIORITY 6

static StaticTask_t nav_board_task_buf;
static StackType_t nav_board_stack_buf[NAV_BOARD_TASK_STACK_SIZE];

static StaticTask_t car_task_buf;
static StackType_t car_stack_buf[CAR_TASK_STACK_SIZE];

void app_main_task()
{


    led_set(LED_BLUE, 1);

    /* Init debug uart */
    log_config_t log_cfg = {
        .uart_handle = &huart2,
    };

    log_init(&log_cfg);

    LOG_INFO("App started\n");

    fault_init();

   /* app_uart_handle_t gps_uart_handle;
    app_uart_init(&gps_uart_handle, &huart3, true, false);  */


    app_i2c_handle_t imu_handle;
    app_i2c_init(&imu_handle, &hi2c1);
    fxos8700_init(&imu_handle);

    xyz_data_t accel_data = {};
    xyz_data_t mag_data = {};

    xTaskCreateStatic(nav_board_handler_task, "nav_board", NAV_BOARD_TASK_STACK_SIZE, NULL, NAV_BOARD_TASK_PRIORITY, nav_board_stack_buf, &nav_board_task_buf);
    xTaskCreateStatic(car_task, "car", CAR_TASK_STACK_SIZE, NULL, CAR_TASK_PRIORITY, car_stack_buf, &car_task_buf);
    
    
    while(1)
    {
        vTaskDelay(10000 / portTICK_PERIOD_MS);
        LOG_INFO("App tick\n");
        //fxso8700_read_data(&accel_data, &mag_data);


    }
}