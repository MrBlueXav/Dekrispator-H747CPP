/**
 ******************************************************************************
 * File Name          : sinetable.h
 * Author				: Xavier Halgand
 * Date               :
 * Description        :
 ******************************************************************************
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __sinetable_h_
#define __sinetable_h_

#ifdef __cplusplus
 extern "C" {
#endif
/*-----------------------------------------------------------------------------*/

#include <math.h>
#include "constants.h"

/*-------------------------------------------------------------------------------*/

#define SINETABLE_SIZE 	1025
#define ALPHA			((SINETABLE_SIZE - 1)/_2PI)

/*-------------------------------------------------------------------------------*/
void sinetable_init(void);

extern const float_t sinetableConst[SINETABLE_SIZE];
extern float_t sinetable[SINETABLE_SIZE];

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
 }
#endif

#endif // __sinetable_h_

