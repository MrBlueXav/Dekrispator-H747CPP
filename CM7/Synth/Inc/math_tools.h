/**
 ******************************************************************************
 * File Name          	: math_tools.h
 * Author				: Xavier Halgand
 * Date               	:
 * Description        	:
 ******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MATH_TOOLS_H
#define __MATH_TOOLS_H

#ifdef __cplusplus
 extern "C" {
#endif

/*-------------------------------------------------------*/

#include <math.h>
#include <stdint.h>
#include "constants.h"

/*-------------------------------------------------------*/
float 	approx_exp(float x);
float	Lin2Exp(uint8_t val, float min, float max); // input val in 0 ... 127
float 	tanhXdX(float x);
float 	fastTanh(float var);
float 	softClipTwo(float in);
float 	fastTan(float x);

#ifdef __cplusplus
 }
#endif

/*-------------------------------------------------------*/
#endif /* __MATH_TOOLS_H */
