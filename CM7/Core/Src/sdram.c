/**
 ******************************************************************************
 * @file    BSP/CM7/Src/sdram.c
 * @author  MCD Application Team
 * @brief   This example code shows how to use the SDRAM Driver
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2019 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "sdram.h"

/** @addtogroup STM32H7xx_HAL_Examples
 * @{
 */

/** @addtogroup BSP
 * @{
 */

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define SDRAM_WRITE_READ_ADDR		0xD0400000
#define BUFFER_SIZE					256
#define WRITE_READ_ADDR				((uint32_t)0x1000)
#define TEST_BUFF_SIZE 				256

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static uint32_t sdram_aTxBuffer[BUFFER_SIZE];
static uint32_t sdram_aRxBuffer[BUFFER_SIZE];

/* 1MB test ---------------------------------------*/

static uint32_t _SDRAM_ test_buff[TEST_BUFF_SIZE];

/* DMA transfer complete flag */
__IO uint32_t uwMDMA_Transfer_Complete = 0;

/* Private function prototypes -----------------------------------------------*/
static void Fill_Buffer(uint32_t *pBuffer, uint32_t uwBufferLenght,
		uint32_t uwOffset);
static uint8_t Buffercmp(uint32_t *pBuffer1, uint32_t *pBuffer2,
		uint16_t BufferLength);
/* Private functions ---------------------------------------------------------*/

/**
 * @brief  SDRAM Demo
 * @param  None
 * @retval None
 */
void SDRAM_test(void) {

	/* SDRAM device configuration */
	if (BSP_SDRAM_Init(0) != BSP_ERROR_NONE) {
		Error_Handler();
//    UTIL_LCD_DisplayStringAt(20, 115, (uint8_t *)"SDRAM Initialization : FAILED.", LEFT_MODE);
//    UTIL_LCD_DisplayStringAt(20, 130, (uint8_t *)"SDRAM Test Aborted.", LEFT_MODE);
	} else {
//    UTIL_LCD_DisplayStringAt(20, 100, (uint8_t *)"SDRAM Initialization : OK.", LEFT_MODE);
	}

	for (uint32_t i = 0; i < TEST_BUFF_SIZE; i++) {
		test_buff[i] = i;
	}
	for (uint32_t i = 0; i < TEST_BUFF_SIZE; i++) {
		if (test_buff[i] != i) {
			Error_Handler();
		}
	}
	/* Fill the buffer to write */
	Fill_Buffer(sdram_aTxBuffer, BUFFER_SIZE, 0xA244250F);

	/* Write data to the SDRAM memory */
	if (HAL_SDRAM_Write_32b(&hsdram[0],
			(uint32_t*) (SDRAM_WRITE_READ_ADDR + WRITE_READ_ADDR),
			(uint32_t*) sdram_aTxBuffer, BUFFER_SIZE) != BSP_ERROR_NONE) {
		Error_Handler();
//    UTIL_LCD_DisplayStringAt(20, 115, (uint8_t *)"SDRAM WRITE : FAILED.", LEFT_MODE);
//    UTIL_LCD_DisplayStringAt(20, 130, (uint8_t *)"SDRAM Test Aborted.", LEFT_MODE);
	} else {
//    UTIL_LCD_DisplayStringAt(20, 115, (uint8_t *)"SDRAM WRITE : OK.", LEFT_MODE);
	}

	/* Read back data from the SDRAM memory */
	if (HAL_SDRAM_Read_32b(&hsdram[0],
			(uint32_t*) (SDRAM_WRITE_READ_ADDR + WRITE_READ_ADDR),
			(uint32_t*) sdram_aRxBuffer, BUFFER_SIZE) != BSP_ERROR_NONE) {
		Error_Handler();
//    UTIL_LCD_DisplayStringAt(20, 130, (uint8_t *)"SDRAM READ : FAILED.", LEFT_MODE);
//    UTIL_LCD_DisplayStringAt(20, 145, (uint8_t *)"SDRAM Test Aborted.", LEFT_MODE);
	} else {
//    UTIL_LCD_DisplayStringAt(20, 130, (uint8_t *)"SDRAM READ : OK.", LEFT_MODE);
	}

	if (Buffercmp(sdram_aTxBuffer, sdram_aRxBuffer, BUFFER_SIZE) > 0) {
		Error_Handler();
//    UTIL_LCD_DisplayStringAt(20, 145, (uint8_t *)"SDRAM COMPARE : FAILED.", LEFT_MODE);
//    UTIL_LCD_DisplayStringAt(20, 160, (uint8_t *)"SDRAM Test Aborted.", LEFT_MODE);
	} else {
//    UTIL_LCD_DisplayStringAt(20, 145, (uint8_t *)"SDRAM Test : OK.", LEFT_MODE);
	}

}

/**
 * @brief  SDRAM DMA Demo
 * @param  None
 * @retval None
 */
void SDRAM_DMA_test(void) {

	//SdramTest = 1;
	BSP_SDRAM_DeInit(0);
	/* SDRAM device configuration */
	if (BSP_SDRAM_Init(0) != BSP_ERROR_NONE) {
		Error_Handler();
//    BSP_LCD_DisplayOn(0);
//    UTIL_LCD_DisplayStringAt(20, 115, (uint8_t *)"SDRAM Initialization : FAILED.", LEFT_MODE);
//    UTIL_LCD_DisplayStringAt(20, 130, (uint8_t *)"SDRAM Test Aborted.", LEFT_MODE);
	} else {
//    BSP_LCD_DisplayOn(0);
//    UTIL_LCD_DisplayStringAt(20, 100, (uint8_t *)"SDRAM Initialization : OK.", LEFT_MODE);
	}
	/* Fill the buffer to write */
	Fill_Buffer(sdram_aTxBuffer, BUFFER_SIZE, 0xA244250F);
//  BSP_LCD_DisplayOn(0);
	/* Write data to the SDRAM memory */
	uwMDMA_Transfer_Complete = 0;
	if (HAL_SDRAM_Write_DMA(&hsdram[0],
			(uint32_t*) (SDRAM_WRITE_READ_ADDR + WRITE_READ_ADDR),
			sdram_aTxBuffer, BUFFER_SIZE) != BSP_ERROR_NONE) {
		Error_Handler();
//    UTIL_LCD_DisplayStringAt(20, 115, (uint8_t *)"SDRAM WRITE : FAILED.", LEFT_MODE);
//    UTIL_LCD_DisplayStringAt(20, 130, (uint8_t *)"SDRAM Test Aborted.", LEFT_MODE);
	} else {
//    UTIL_LCD_DisplayStringAt(20, 115, (uint8_t *)"SDRAM WRITE : OK.", LEFT_MODE);
	}
	/* Wait until DMA transfer is complete */
	while (!uwMDMA_Transfer_Complete) {
	}

	/* Read back data from the SDRAM memory */
	uwMDMA_Transfer_Complete = 0;
	if (HAL_SDRAM_Read_DMA(&hsdram[0],
			(uint32_t*) (SDRAM_WRITE_READ_ADDR + WRITE_READ_ADDR),
			sdram_aRxBuffer, BUFFER_SIZE) != BSP_ERROR_NONE) {
		Error_Handler();
//    UTIL_LCD_DisplayStringAt(20, 130, (uint8_t *)"SDRAM READ : FAILED.", LEFT_MODE);
//    UTIL_LCD_DisplayStringAt(20, 145, (uint8_t *)"SDRAM Test Aborted.", LEFT_MODE);
	} else {
//    UTIL_LCD_DisplayStringAt(20, 130, (uint8_t *)"SDRAM READ : OK.", LEFT_MODE);
	}
	/* Wait until DMA transfer is complete */
	while (!uwMDMA_Transfer_Complete) {
	}

	if (Buffercmp(sdram_aTxBuffer, sdram_aRxBuffer, BUFFER_SIZE) > 0) {
		Error_Handler();
//    UTIL_LCD_DisplayStringAt(20, 145, (uint8_t *)"SDRAM COMPARE : FAILED.", LEFT_MODE);
//    UTIL_LCD_DisplayStringAt(20, 160, (uint8_t *)"SDRAM Test Aborted.", LEFT_MODE);
	} else {
//    UTIL_LCD_DisplayStringAt(20, 145, (uint8_t *)"SDRAM Test : OK.", LEFT_MODE);
	}

}

/**
 * @brief  Fills buffer with user predefined data.
 * @param  pBuffer: pointer on the buffer to fill
 * @param  uwBufferLenght: size of the buffer to fill
 * @param  uwOffset: first value to fill on the buffer
 * @retval None
 */
static void Fill_Buffer(uint32_t *pBuffer, uint32_t uwBufferLength,
		uint32_t uwOffset) {
	uint32_t tmpIndex = 0;

	/* Put in global buffer different values */
	for (tmpIndex = 0; tmpIndex < uwBufferLength; tmpIndex++) {
		pBuffer[tmpIndex] = tmpIndex + uwOffset;
	}
	/* Clean Data Cache to update the content of the SDRAM */
	SCB_CleanDCache_by_Addr((uint32_t*) pBuffer, uwBufferLength * 4);
}

/**
 * @brief  Compares two buffers.
 * @param  pBuffer1, pBuffer2: buffers to be compared.
 * @param  BufferLength: buffer's length
 * @retval 1: pBuffer identical to pBuffer1
 *         0: pBuffer differs from pBuffer1
 */
static uint8_t Buffercmp(uint32_t *pBuffer1, uint32_t *pBuffer2,
		uint16_t BufferLength) {
	/* Invalidate Data Cache to get the updated content of the SRAM*/
	SCB_CleanInvalidateDCache_by_Addr((uint32_t*) pBuffer2, BufferLength * 4);

	while (BufferLength--) {
		if (*pBuffer1 != *pBuffer2) {
			return 1;
		}

		pBuffer1++;
		pBuffer2++;
	}

	return 0;
}

/**
 * @brief  DMA conversion complete callback
 * @note   This function is executed when the transfer complete interrupt
 *         is generated
 * @retval None
 */
void HAL_SDRAM_DMA_XferCpltCallback(MDMA_HandleTypeDef *hmdma) {
	/* Set transfer complete flag */
	uwMDMA_Transfer_Complete = 1;
}

/**
 * @brief  DMA transfer complete error callback.
 * @param  hdma: DMA handle
 * @retval None
 */
void HAL_SDRAM_DMA_XferErrorCallback(MDMA_HandleTypeDef *hmdma) {
	Error_Handler();
//  UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_RED);
//  UTIL_LCD_DisplayStringAt(20, 215, (uint8_t *)"MDMA ERROR", LEFT_MODE);
}
