/**
 ******************************************************************************
 * @file    audio_play.c
 * @author  Xavier Halgand
 * @brief   2024
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "audio_play.h"
#include "stm32h747i_discovery.h"
#include "openamp_interface.h"
#include <stdio.h>
#include "stm32h7xx_hal.h"
#include "stm32h747i_discovery_audio.h"
#include "soundGen.h"
#include "perf.h"
#include "constants.h"

char string_message[100];

/* Private typedef -----------------------------------------------------------*/
typedef enum {
	AUDIO_ERROR_NONE = 0, AUDIO_ERROR_NOTREADY, AUDIO_ERROR_IO, AUDIO_ERROR_EOF,

} AUDIO_ErrorTypeDef;

typedef enum {
	AUDIO_STATE_IDLE = 0,
	AUDIO_STATE_INIT,
	AUDIO_STATE_PLAYING,
	AUDIO_STATE_PAUSE

} AUDIO_PLAYBACK_StateTypeDef;

typedef enum {
	BUFFER_OFFSET_NONE = 0, BUFFER_OFFSET_HALF, BUFFER_OFFSET_FULL,

} BUFFER_StateTypeDef;

typedef struct {
	uint8_t buff[AUDIO_BUFFER_SIZE]; // AUDIO_BUFFER_SIZE is defined in constants.h
	BUFFER_StateTypeDef state;

} AUDIO_BufferTypeDef;

/* Private variables ---------------------------------------------------------*/
//ALIGN_32BYTES(static volatile AUDIO_BufferTypeDef buffer_ctl);

ALIGN_32BYTES(static uint8_t buff[AUDIO_BUFFER_SIZE]); // AUDIO_BUFFER_SIZE is defined in constants.h
static volatile BUFFER_StateTypeDef state;
static AUDIO_PLAYBACK_StateTypeDef audio_state;
static bool sound = true;
static volatile uint32_t uwVolume;
static BSP_AUDIO_Init_t AudioPlayInit;

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Audio Play demo
 * @param  None
 * @retval None
 */
void AudioInit(void) {
	uwVolume = VOL;

	AudioPlayInit.Device = AUDIO_OUT_DEVICE_HEADPHONE;
	AudioPlayInit.ChannelsNbr = 2;
	AudioPlayInit.SampleRate = SAMPLERATE;
	AudioPlayInit.BitsPerSample = AUDIO_RESOLUTION_16B;
	AudioPlayInit.Volume = uwVolume;

	if (BSP_AUDIO_OUT_Init(0, &AudioPlayInit) != BSP_ERROR_NONE) {
		Error_Handler();
	}
	HAL_Delay(500);

	/*
	 Start playing the file from a circular buffer, once the DMA is enabled, it is
	 always in running state. Application has to fill the buffer with the audio data
	 using Transfer complete and/or half transfer complete interrupts callbacks
	 (AUDIO_TransferComplete_CallBack() or AUDIO_HalfTransfer_CallBack()...
	 */
	state = BUFFER_OFFSET_NONE;
	BSP_AUDIO_OUT_Play(0, (uint8_t*) &buff[0], AUDIO_BUFFER_SIZE);
	audio_state = AUDIO_STATE_PLAYING;
}

/*----------------------------------------------------------------------------------------------------*/
uint8_t AUDIO_Process(void) {
	AUDIO_ErrorTypeDef error_state = AUDIO_ERROR_NONE;

	switch (audio_state) {
	case AUDIO_STATE_PLAYING:

		//BSP_LED_Off(LED_ORANGE); // CPU load indicator

		/* 1st half buffer played; so fill it and continue playing from bottom*/
		if (state == BUFFER_OFFSET_HALF) {
			cyc_count_reset();

			make_sound((uint16_t*) &buff[0], AUDIO_BUFFER_SIZE / 8);
			state = BUFFER_OFFSET_NONE;

			/* Clean Data Cache to update the content of the SRAM */
			SCB_CleanDCache_by_Addr((uint32_t*) &buff[0],
			AUDIO_BUFFER_SIZE / 2);
			cyc_count_print();
		}

		/* 2nd half buffer played; so fill it and continue playing from top */
		if (state == BUFFER_OFFSET_FULL) {
			cyc_count_reset();

			make_sound((uint16_t*) &buff[AUDIO_BUFFER_SIZE / 2],
			AUDIO_BUFFER_SIZE / 8);
			state = BUFFER_OFFSET_NONE;

			/* Clean Data Cache to update the content of the SRAM */
			SCB_CleanDCache_by_Addr(
					(uint32_t*) &buff[AUDIO_BUFFER_SIZE / 2],
					AUDIO_BUFFER_SIZE / 2);
			cyc_count_print();
		}

		//BSP_LED_On(LED_ORANGE);

		break;

	default:
		error_state = AUDIO_ERROR_NOTREADY;
		break;
	}

	return (uint8_t) error_state;
}

/*------------------------------------------------------------------------------
 Callbacks implementation:
 the callbacks API are defined __weak in the stm32h747i_discovery_audio.c file
 and their implementation should be done the user code if they are needed.
 Below some examples of callback implementations.
 ----------------------------------------------------------------------------*/
/**
 * @brief  Manages the full Transfer complete event.
 * @param  None
 * @retval None
 */
void BSP_AUDIO_OUT_TransferComplete_CallBack(uint32_t Instance) {
	if (audio_state == AUDIO_STATE_PLAYING) {
		/* allows AUDIO_Process() to refill 2nd part of the buffer  */
		state = BUFFER_OFFSET_FULL;
	}
}
/*----------------------------------------------------------------------------------------------------*/
/**
 * @brief  Manages the DMA Half Transfer complete event.
 * @param  None
 * @retval None
 */
void BSP_AUDIO_OUT_HalfTransfer_CallBack(uint32_t Instance) {
	if (audio_state == AUDIO_STATE_PLAYING) {
		/* allows AUDIO_Process() to refill 1st part of the buffer  */
		state = BUFFER_OFFSET_HALF;
	}
}
/*----------------------------------------------------------------------------------------------------*/
/**
 * @brief  Manages the DMA FIFO error event.
 * @param  None
 * @retval None
 */
void BSP_AUDIO_OUT_Error_CallBack(uint32_t Instance) {
	BSP_LED_On(LED_RED);
}

//--------------------------------- toggle ON/OFF volume ------------------------------------------
void toggleSound(void) {
	if (!sound) {
		//pitchGenResetPhase();
		BSP_AUDIO_OUT_SetVolume(0, uwVolume);
		sound = true;
	} else {
		BSP_AUDIO_OUT_SetVolume(0, 0);
		sound = false;
	}
}
//------------------------------- increase output DAC volume --------------------------------------------
void incVol(void) {
	if (uwVolume < MAXVOL) {
		uwVolume++;
		BSP_AUDIO_OUT_SetVolume(0, uwVolume);
	}
	sprintf(string_message, "Volume is now : %lu            ", uwVolume);
	send_string_to_CM4(string_message);
}

//-------------------------------- decrease output DAC volume ------------------------------------------
void decVol(void) {
	if (uwVolume > 0) {
		uwVolume--;
		BSP_AUDIO_OUT_SetVolume(0, uwVolume);
	}
	sprintf(string_message, "Volume is now : %lu            ", uwVolume);
	send_string_to_CM4(string_message);
}

//------------------------------------------------------------------------------------------------------
void Volume_set(uint8_t val) {
	uwVolume = (uint8_t) (MAXVOL / MIDI_MAX * val);
	BSP_AUDIO_OUT_SetVolume(0, uwVolume);
}

/*-------------------------------- END OF FILE -------------------------------------------------------------------------*/
