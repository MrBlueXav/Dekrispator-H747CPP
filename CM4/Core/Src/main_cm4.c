/**
 ******************************************************************************
 * 					DEKRISPATOR H747
 * @file           : main_cm4.c
 * @brief          : Main program body for CM4
 * @date			: april 2024
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main_cm4.h"
#include "rtc.h"
#include "usart.h"
#include "usb_host.h"
#include "gpio.h"
#include "stdio.h"
#include "stm32h747i_discovery.h"
#include "stm32h747i_discovery_lcd.h"
#include "stm32_lcd.h"
#include "lcd_trace.h"
#include "interface.h"
#include "qspi.h"

#ifndef HSEM_ID_0
#define HSEM_ID_0 (0U) /* HW semaphore 0*/
#endif

/*---------------------------------------------------------------------------------------------*/
void BSP_LED_Initialize(void);
void Welcome_message(void);

/*---------------------------------------------------------------------------------------------*/
/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
	/*HW semaphore Clock enable*/
	__HAL_RCC_HSEM_CLK_ENABLE();
	/* Activate HSEM notification for Cortex-M4*/
	HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_0));
	/*
	 Domain D2 goes to STOP mode (Cortex-M4 in deep-sleep) waiting for Cortex-M7 to
	 perform system initialization (system clock config, external memory configuration.. )
	 */
	HAL_PWREx_ClearPendingEvent();
	HAL_PWREx_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_STOPENTRY_WFE, PWR_D2_DOMAIN);
	/* Clear HSEM flag */
	__HAL_HSEM_CLEAR_FLAG(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_0));

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	BSP_LED_Initialize();
	MX_RTC_Init();
	MX_USART1_UART_Init();

	printf("\n");
	printf("-----------------------------------------\n");
	printf("Starting Dekrispator H747...\n");
	printf("-----------------------------------------\n");

	/* Configure the Wakeup push-button and joystick in EXTI Mode */
	BSP_PB_Init(BUTTON_WAKEUP, BUTTON_MODE_EXTI);
	BSP_JOY_Init(JOY1, JOY_MODE_EXTI, JOY_ALL);

#if (USE_THE_LCD > 0)
	/* Initialize the LCD */
	BSP_LCD_Init(0, LCD_ORIENTATION_LANDSCAPE);
	UTIL_LCD_SetFuncDriver(&LCD_Driver);
#endif

	MX_USB_HOST_Init();
	QSPI_init();
	Welcome_message();
	QSPI_ReInit();
	openamp_init();
	/* CM7_SEV_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(CM7_SEV_IRQn, 10, 0);
	HAL_NVIC_EnableIRQ(CM7_SEV_IRQn);

	printf("\n");
	printf("-----------------------------------------\n");
	printf("****    This is Dekrispator H747 !   ****\n");
	printf("Waiting for USB MIDI controller device...\n");
	printf("-----------------------------------------\n");
	printf("\n");

	while (1)
	{
		MX_USB_HOST_Process();
		Application_Process(); // in interface.c
	}
}
/*********************************************************************************************/
void BSP_LED_Initialize(void)
{
	BSP_LED_Init(LED1);
	BSP_LED_Init(LED2);
	BSP_LED_Init(LED3);
	BSP_LED_Init(LED4);
	BSP_LED_On(LED1);
	BSP_LED_On(LED2);
	BSP_LED_On(LED3);
	BSP_LED_On(LED4);
	HAL_Delay(300);
	BSP_LED_Off(LED1);
	BSP_LED_Off(LED2);
	BSP_LED_Off(LED3);
	BSP_LED_Off(LED4);
}
/*--------------------------------------------------------------------------------------*/
void Welcome_message(void)
{
#if (USE_THE_LCD > 0)

	if (BSP_QSPI_EnableMemoryMappedMode(0) != BSP_ERROR_NONE)
	{
		printf("QSPI Memory Mapped Mode : FAILED\n");
	}
	else
	{
		printf("QSPI Memory Mapped Mode : OK\n");
		BSP_LCD_DrawBitmap(0, 0, 0, (uint8_t*) BACKGRND_ADDR); /* Display main screen on LCD */
	}

	UTIL_LCD_SetFont(&Font20);
	UTIL_LCD_SetTextColor(UTIL_LCD_COLOR_BLACK);
	UTIL_LCD_SetBackColor(UTIL_LCD_COLOR_WHITE);

#endif
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	BSP_LED_On(LED_RED);
	while (1)
	{
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
