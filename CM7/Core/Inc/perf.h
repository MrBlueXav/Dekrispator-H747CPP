/*
 * 	File : perf.h
 *	Performance measurements using Data Watchpoint and Trace unit (DWT)
 *	Present on all STM32 using the CM3, CM4 and CM7 cores.
 *  Created on: Jan 13, 2024
 *      Author: X. Halgand
 */

#ifndef INC_PERF_H_
#define INC_PERF_H_

#ifdef __cplusplus
 extern "C" {
#endif

/*******************************************************************************/
#include <stdint.h>

/*******************************************************************************/
void EnableTiming(void);
void cyc_count_reset(void);
uint32_t cyc_count_get(void);
void cyc_count_print(void);
void Delay(uint32_t cycles);

#ifdef __cplusplus
 }
#endif

/*******************************************************************************/
#endif /* INC_PERF_H_ */
