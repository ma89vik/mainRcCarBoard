#include "led.h"
#include "gpio.h"
#include "error_def.h"


typedef struct {
    const led_t led;
    GPIO_TypeDef* GPIOx;
    const uint16_t pin;
} led_map_item_t;

/* Order must match led_t */
static const led_map_item_t led_map[] = {
  {LED_GREEN,   GPIOD,  GPIO_PIN_12},   
  {LED_ORANGE,  GPIOD,  GPIO_PIN_13},  
  {LED_RED,     GPIOD,  GPIO_PIN_14},   
  {LED_BLUE,    GPIOD,  GPIO_PIN_15}, 
};


err_def_t led_set(led_t led, int value)
{
    if (led >= LED_MAX) {
        return ERR_INVALID_ARGS;
    }

    HAL_GPIO_WritePin(led_map[led].GPIOx, led_map[led].pin, value);

    return ERR_OK;
}