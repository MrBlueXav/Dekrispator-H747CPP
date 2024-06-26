/**
 ******************************************************************************
 * File Name          : delay.h
 * Author				: Xavier Halgand
 * Date               :
 * Description        :
 ******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DELAY_H
#define __DELAY_H

#ifdef __cplusplus
 extern "C" {
#endif

/*--------------------------------------------------------------------------- */

#define DELAYLINE_LEN           48000  // max delay in samples (30000 is 0.625 seconds)
#define INIT_DELAY              12000  // init delay (in samples)
#define INIT_FEEDB              0.4f
#define INIT_WET				0.5f
#define MIN_DELAY				250		// min delay, in samples
#define DELTA_DELAY				20		// variation step of delay time

/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include <math.h>
#include "constants.h"

/*----------------------------------------------------------------------------*/
typedef struct
{
	uint32_t	shift;
	float		coeff_a1;
	float 		fdb;
	float		wet;

} DelayParams_t;

/* Exported functions --------------------------------------------------------*/

void 	Delay_init(void);
void 	Delay_clean(void);
void 	Delay_params_set(const DelayParams_t *params);
void 	Delay_params_save(DelayParams_t *params);
float	Delay_compute (float x);
void 	Delay_feedback_inc(void);
void	Delay_feedback_dec(void);
void 	DelayFeedback_set(uint8_t val);
void 	DelayWet_set(uint8_t val);
void 	Delay_time_inc(uint8_t val);
void	Delay_time_dec(uint8_t val);
void 	Delay_time_set(uint8_t val);

#ifdef __cplusplus
 }
#endif

//*************************************************************************************************
#endif
