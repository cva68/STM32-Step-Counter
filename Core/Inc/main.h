/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32c0xx_hal.h"

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
#define SW1_Pin GPIO_PIN_11
#define SW1_GPIO_Port GPIOC
#define RGB_DS4_Pin GPIO_PIN_12
#define RGB_DS4_GPIO_Port GPIOC
#define SW4_Pin GPIO_PIN_13
#define SW4_GPIO_Port GPIOC
#define RGB_DS1_Pin GPIO_PIN_3
#define RGB_DS1_GPIO_Port GPIOF
#define SW2_Pin GPIO_PIN_1
#define SW2_GPIO_Port GPIOC
#define RGB_DS2_Pin GPIO_PIN_2
#define RGB_DS2_GPIO_Port GPIOC
#define NUCLEO_LD1_Pin GPIO_PIN_5
#define NUCLEO_LD1_GPIO_Port GPIOA
#define JOYSTICK_X_Pin GPIO_PIN_4
#define JOYSTICK_X_GPIO_Port GPIOC
#define JOYSTICK_Y_Pin GPIO_PIN_5
#define JOYSTICK_Y_GPIO_Port GPIOC
#define JOYSTICK_CLICK_Pin GPIO_PIN_1
#define JOYSTICK_CLICK_GPIO_Port GPIOB
#define IMU_SPI_nSS_Pin GPIO_PIN_12
#define IMU_SPI_nSS_GPIO_Port GPIOB
#define IMU_SPI_CLOCK_Pin GPIO_PIN_13
#define IMU_SPI_CLOCK_GPIO_Port GPIOB
#define IMU_SPI_MISO_Pin GPIO_PIN_14
#define IMU_SPI_MISO_GPIO_Port GPIOB
#define IMU_SPI_MOSI_Pin GPIO_PIN_15
#define IMU_SPI_MOSI_GPIO_Port GPIOB
#define NUCLEO_LD2_Pin GPIO_PIN_9
#define NUCLEO_LD2_GPIO_Port GPIOC
#define RGB_GREEN_Pin GPIO_PIN_2
#define RGB_GREEN_GPIO_Port GPIOD
#define RGB_RED_Pin GPIO_PIN_3
#define RGB_RED_GPIO_Port GPIOD
#define RGB_BLUE_Pin GPIO_PIN_4
#define RGB_BLUE_GPIO_Port GPIOD
#define SW3_Pin GPIO_PIN_10
#define SW3_GPIO_Port GPIOC
#define SW3_EXTI_IRQn EXTI4_15_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
