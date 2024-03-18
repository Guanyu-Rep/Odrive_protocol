/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define LED_G(n)			(n?HAL_GPIO_WritePin(RED_GPIO_Port,RED_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(RED_GPIO_Port,RED_Pin,GPIO_PIN_RESET))
#define LED_G_TogglePin		HAL_GPIO_TogglePin(RED_GPIO_Port,RED_Pin)	//LED_R电平翻转

#define LED_R(n)			(n?HAL_GPIO_WritePin(GREEN_GPIO_Port,GREEN_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(GREEN_GPIO_Port,GREEN_Pin,GPIO_PIN_RESET))
#define LED_R_TogglePin     HAL_GPIO_TogglePin(GREEN_GPIO_Port,GREEN_Pin)	//LED_B电平翻转
/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

