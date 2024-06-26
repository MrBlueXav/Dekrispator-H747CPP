/*
 * qspi.h
 *
 *  Created on: Jan 18, 2024
 *      Author: XavSab
 */

#ifndef INC_QSPI_H_
#define INC_QSPI_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "string.h"
#include "stm32h7xx_hal.h"
#include "stm32h747i_discovery.h"
#include "stm32h747i_discovery_lcd.h"
#include "stm32h747i_discovery_conf.h"
//#include "stm32h747i_discovery_sd.h"
#include "stm32h747i_discovery_ts.h"
//#include "stm32h747i_discovery_audio.h"
#include "stm32h747i_discovery_qspi.h"
//#include "stm32h747i_discovery_camera.h"
#include "stm32h747i_discovery_sdram.h"
#include "stm32_lcd.h"


void QSPI_init (void);
void QSPI_ReInit(void);
void QSPI_SetHint(void);

#ifdef __cplusplus
}
#endif

#endif /* INC_QSPI_H_ */
