#include "led.h"
#include "gpio.h"
#include "error_def.h"


typedef struct {
    led_t led;
    GPIO_TypeDef* GPIOx;
    uint16_t pin;
} led_map_item_t;

/* Order must match led_t */
static led_map_item_t led_map[] = {
  {LED_GREEN,   LED_GREEN_GPIO_Port,  LED_GREEN_Pin},
  {LED_ORANGE,  LED_YELLOW_GPIO_Port,  LED_YELLOW_Pin},
  {LED_BLUE,    LED_BLUE_GPIO_Port,  LED_BLUE_Pin},
};


err_def_t led_set(led_t led, int value)
{
    if (led >= LED_MAX) {
        return ERR_INVALID_ARGS;
    }

    HAL_GPIO_WritePin(led_map[led].GPIOx, led_map[led].pin, value);

    return ERR_OK;
}