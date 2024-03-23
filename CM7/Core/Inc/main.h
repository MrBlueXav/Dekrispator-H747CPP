/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h for M7 core
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
//#include "stm32h7xx_hal_conf.h"
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_sdram.h"
#include "openamp_interface.h"
#include "rng.h"
#include "gpio.h"
#include "perf.h"
//#include "stm32h747i_discovery_lcd.h"
#include "stm32h747i_discovery.h"
#include "stm32h747i_discovery_audio.h"
#include "stm32h747i_discovery_sdram.h"
#include "audio_play.h"
#include "MIDI_application.h"
#include "soundGen.h"
#include "sdram.h"

/* Private includes ----------------------------------------------------------*/



/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* Private defines -----------------------------------------------------------*/
#define OSC32_OUT_Pin GPIO_PIN_15
#define OSC32_OUT_GPIO_Port GPIOC
#define OSC32_IN_Pin GPIO_PIN_14
#define OSC32_IN_GPIO_Port GPIOC
#define CEC_CK_MCO1_Pin GPIO_PIN_8
#define CEC_CK_MCO1_GPIO_Port GPIOA
#define OSC_OUT_Pin GPIO_PIN_1
#define OSC_OUT_GPIO_Port GPIOH
#define OSC_IN_Pin GPIO_PIN_0
#define OSC_IN_GPIO_Port GPIOH

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
