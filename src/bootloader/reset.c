#include "reset.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_rcc.h"
#include "printf.h"

typedef enum {
    RESET_REASON_NONE = -1,
    RESET_REASON_BROWN_OUT,
    RESET_REASON_PIN,
    RESET_REASON_POR,
    RESET_REASON_SW,
    RESET_REASON_WDT,
    RESET_REASON_WINDOW_WD,
    RESET_REASON_LOW_PWR,
    RESET_REASON_MAX,
} reset_reason_t;

static reset_reason_t reset_reason = RESET_REASON_NONE;

static char *reset_strings[RESET_REASON_MAX] = {
    "Reset due to brown out, RCC_FLAG_BORRST set\n",
    "Reset due reset pin pulled high, RCC_FLAG_PINRST set\n",
    "Reset due to power on/power down, RCC_FLAG_PORRST set\n",
    "Reset by software, RCC_FLAG_SFTRST set\n",
    "Reset by the independant watchdog, RCC_FLAG_IWDGRST set\n",
    "Reset by the window watchdog, RCC_FLAG_WWDGRST set\n",
    "Reset by low-power management, RCC_FLAG_LPWRRST set\n",
};

void reset(void)
{
    HAL_NVIC_SystemReset();
}

void reset_save_reason()
{
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_BORRST)) {
        reset_reason = RESET_REASON_BROWN_OUT;
    } else if (__HAL_RCC_GET_FLAG(RCC_FLAG_PINRST)){
        reset_reason = RESET_REASON_PIN;
    } else if (__HAL_RCC_GET_FLAG(RCC_FLAG_PORRST)){
        reset_reason = RESET_REASON_POR;
    } else if (__HAL_RCC_GET_FLAG(RCC_FLAG_SFTRST)){
        reset_reason = RESET_REASON_SW;
    } else if (__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST)){
        reset_reason = RESET_REASON_WDT;
    } else if (__HAL_RCC_GET_FLAG(RCC_FLAG_WWDGRST)){
        reset_reason = RESET_REASON_WINDOW_WD;
    } else if (__HAL_RCC_GET_FLAG(RCC_FLAG_LPWRRST)){
        reset_reason = RESET_REASON_LOW_PWR;
    } else {
        reset_reason = RESET_REASON_NONE;
    }

    __HAL_RCC_CLEAR_RESET_FLAGS();
}


/* Prints the last reset reason and resets flags*/
void reset_print_and_clear_reason()
{
    if (reset_reason == RESET_REASON_NONE) {
        printf("No reset reason\n");
    } else {
        printf("%s", reset_strings[reset_reason]);
    }
}