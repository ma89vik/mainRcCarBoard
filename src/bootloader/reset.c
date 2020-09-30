#include "reset.h"
#include "stm32f4xx_hal.h"
#include "printf.h"

void reset(void)
{
    HAL_NVIC_SystemReset();
}

/* Prints the last reset reason */
void reset_print_reason(void)
{

}