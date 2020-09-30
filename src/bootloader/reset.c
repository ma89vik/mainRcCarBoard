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

reset_reason_t reset_get_reason()
{
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_BORRST)) {
        return RESET_REASON_BROWN_OUT;
    } else if (__HAL_RCC_GET_FLAG(RCC_FLAG_PINRST)){
        return RESET_REASON_PIN;
    } else if (__HAL_RCC_GET_FLAG(RCC_FLAG_PORRST)){
        return RESET_REASON_POR;
    } else if (__HAL_RCC_GET_FLAG(RCC_FLAG_SFTRST)){
        printf("SW\n");
        return RESET_REASON_SW;
    } else if (__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST)){
        return RESET_REASON_WDT;
    } else if (__HAL_RCC_GET_FLAG(RCC_FLAG_WWDGRST)){
        return RESET_REASON_WINDOW_WD;
    } else if (__HAL_RCC_GET_FLAG(RCC_FLAG_LPWRRST)){
        return RESET_REASON_LOW_PWR;
    }
    return RESET_REASON_NONE;
}


/* Prints the last reset reason and resets flags*/
void reset_print_and_clear_reason()
{
    reset_reason_t reason = reset_get_reason();
    printf("%s", reset_strings[reason]);
    __HAL_RCC_CLEAR_RESET_FLAGS();
}