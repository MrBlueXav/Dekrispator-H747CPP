/*
 * audio_play.h
 *
 *  Created on: Dec 2, 2023
 *      Author: XavSab
 */

#ifndef APPLICATION_USER_CM7_INC_AUDIO_PLAY_H_
#define APPLICATION_USER_CM7_INC_AUDIO_PLAY_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Exported functions ------------------------------------------------------- */
void 	AudioInit (void);
uint8_t AUDIO_Process(void);
void 	Error_Handler(void);
void 	toggleSound(void);
void 	incVol(void);
void 	decVol(void);
void 	Volume_set(uint8_t val);

#ifdef __cplusplus
 }
#endif

#endif /* APPLICATION_USER_CM7_INC_AUDIO_PLAY_H_ */
