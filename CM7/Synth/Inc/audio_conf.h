/**
 ******************************************************************************
 * File Name          : audio_conf.h
 * Author				: Xavier Halgand
 * Date               :
 * Description        :
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AUDIO_CONF_H
#define __AUDIO_CONF_H

#ifdef __cplusplus
 extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>
#include "constants.h"
#include "stm32h747i_discovery.h"
#include "stm32h747i_discovery_audio.h"
#include "soundGen.h"
#include "main.h"

/* Exported functions ------------------------------------------------------- */
//void audio_init(void);
void toggleSound(void);
void incVol(void);
void decVol(void);
void Volume_set(uint8_t val);

#ifdef __cplusplus
 }
#endif

#endif /* __AUDIO_H */
