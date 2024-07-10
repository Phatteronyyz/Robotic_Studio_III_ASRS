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
#include "stm32g4xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define B1_EXTI_IRQn EXTI15_10_IRQn
#define GPIOUT_PushPull_Pin GPIO_PIN_0
#define GPIOUT_PushPull_GPIO_Port GPIOC
#define GPIOUT_Vacuum_Pin GPIO_PIN_1
#define GPIOUT_Vacuum_GPIO_Port GPIOC
#define GPIOUT_Pilot2_Pin GPIO_PIN_4
#define GPIOUT_Pilot2_GPIO_Port GPIOA
#define GPIOIN_LeadMax_Pin GPIO_PIN_6
#define GPIOIN_LeadMax_GPIO_Port GPIOA
#define GPIOIN_LeadMin_Pin GPIO_PIN_7
#define GPIOIN_LeadMin_GPIO_Port GPIOA
#define GPIOUT_Pilot1_Pin GPIO_PIN_0
#define GPIOUT_Pilot1_GPIO_Port GPIOB
#define GPIOIN_LimitMin_Pin GPIO_PIN_1
#define GPIOIN_LimitMin_GPIO_Port GPIOB
#define TIM20CH1_JoySel2_Pin GPIO_PIN_2
#define TIM20CH1_JoySel2_GPIO_Port GPIOB
#define GPIOIN_LimitMax_Pin GPIO_PIN_14
#define GPIOIN_LimitMax_GPIO_Port GPIOB
#define TIM3CH1_JoySave_Pin GPIO_PIN_6
#define TIM3CH1_JoySave_GPIO_Port GPIOC
#define GPIOIN_Emer_Pin GPIO_PIN_7
#define GPIOIN_Emer_GPIO_Port GPIOC
#define TIM20CH3_JoyZDown_Pin GPIO_PIN_8
#define TIM20CH3_JoyZDown_GPIO_Port GPIOC
#define TIM1CH1_EocoderA_Pin GPIO_PIN_8
#define TIM1CH1_EocoderA_GPIO_Port GPIOA
#define TIM1CH2_EncoderB_Pin GPIO_PIN_9
#define TIM1CH2_EncoderB_GPIO_Port GPIOA
#define TIM4CH1_JoySel1_Pin GPIO_PIN_11
#define TIM4CH1_JoySel1_GPIO_Port GPIOA
#define T_SWDIO_Pin GPIO_PIN_13
#define T_SWDIO_GPIO_Port GPIOA
#define T_SWCLK_Pin GPIO_PIN_14
#define T_SWCLK_GPIO_Port GPIOA
#define GPIOUT_DrivINA_Pin GPIO_PIN_15
#define GPIOUT_DrivINA_GPIO_Port GPIOA
#define T_SWO_Pin GPIO_PIN_3
#define T_SWO_GPIO_Port GPIOB
#define TIM8CH1_joyX_Pin GPIO_PIN_6
#define TIM8CH1_joyX_GPIO_Port GPIOB
#define GPIOUT_DrivINB_Pin GPIO_PIN_7
#define GPIOUT_DrivINB_GPIO_Port GPIOB
#define TIM8CH3_JoyZUp_Pin GPIO_PIN_9
#define TIM8CH3_JoyZUp_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
