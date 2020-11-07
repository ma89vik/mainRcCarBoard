/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DEBUG_TX_Pin GPIO_PIN_2
#define DEBUG_TX_GPIO_Port GPIOA
#define DEBUG_RX_Pin GPIO_PIN_3
#define DEBUG_RX_GPIO_Port GPIOA
#define GPS_TX_Pin GPIO_PIN_10
#define GPS_TX_GPIO_Port GPIOB
#define GPS_RX_Pin GPIO_PIN_11
#define GPS_RX_GPIO_Port GPIOB
#define LED_YELLOW_Pin GPIO_PIN_12
#define LED_YELLOW_GPIO_Port GPIOB
#define LED_GREEN_Pin GPIO_PIN_13
#define LED_GREEN_GPIO_Port GPIOB
#define LED_BLUE_Pin GPIO_PIN_14
#define LED_BLUE_GPIO_Port GPIOB
#define MOTOR_PWM_Pin GPIO_PIN_6
#define MOTOR_PWM_GPIO_Port GPIOC
#define SERVO_PWM_Pin GPIO_PIN_7
#define SERVO_PWM_GPIO_Port GPIOC
#define NAV_TX_Pin GPIO_PIN_9
#define NAV_TX_GPIO_Port GPIOA
#define NAV_RX_Pin GPIO_PIN_10
#define NAV_RX_GPIO_Port GPIOA
#define IMU_INT1_Pin GPIO_PIN_10
#define IMU_INT1_GPIO_Port GPIOC
#define IMU_INT2_Pin GPIO_PIN_11
#define IMU_INT2_GPIO_Port GPIOC
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
