/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define BMP280_SDA_Pin GPIO_PIN_0
#define BMP280_SDA_GPIO_Port GPIOF
#define BMP280_SCL_Pin GPIO_PIN_1
#define BMP280_SCL_GPIO_Port GPIOF
#define BLDC1_Pin GPIO_PIN_7
#define BLDC1_GPIO_Port GPIOF
#define BLDC3_Pin GPIO_PIN_8
#define BLDC3_GPIO_Port GPIOF
#define BLDC4_Pin GPIO_PIN_9
#define BLDC4_GPIO_Port GPIOF
#define UPT1_RX_Pin GPIO_PIN_0
#define UPT1_RX_GPIO_Port GPIOA
#define UPT1_TX_Pin GPIO_PIN_1
#define UPT1_TX_GPIO_Port GPIOA
#define BLDC2_Pin GPIO_PIN_14
#define BLDC2_GPIO_Port GPIOB
#define OLED_SDA_Pin GPIO_PIN_9
#define OLED_SDA_GPIO_Port GPIOC
#define OLED_SCL_Pin GPIO_PIN_8
#define OLED_SCL_GPIO_Port GPIOA
#define LORA_RX_Pin GPIO_PIN_12
#define LORA_RX_GPIO_Port GPIOC
#define LORA_TX_Pin GPIO_PIN_2
#define LORA_TX_GPIO_Port GPIOD
#define MPU6050_SCL_Pin GPIO_PIN_6
#define MPU6050_SCL_GPIO_Port GPIOB
#define MPU6050_SDA_Pin GPIO_PIN_7
#define MPU6050_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
