/**
 ******************************************************************************
 * File Name          : drifter.h
 * Author			  : Xavier Halgand
 * Date               :
 * Description        :
 ******************************************************************************
 */

/*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*
*/

#ifndef __DRIFTER_H__
#define __DRIFTER_H__

#ifdef __cplusplus
 extern "C" {
#endif

/************************************************************************************/
#include  <stdint.h>
#include "random.h"
#include "constants.h"

/*---------------------------------------------------------------------------------*/
typedef struct
{
	/*---- parameters ----*/
	float 	    fmax; // sort of max frequency
	float   	fmin; // sort of min frequency
	float   	gain; // drifter output is bound in [-gain, +gain]

	/*---- internals -----*/
	float 		minLength;
	float 		maxLength;
	uint32_t    length;
	uint32_t    n; //sample counter
	float		initial;
	float       final;
	float       slope;

	/*---- output --------*/
	float    	out;

} Drifter_t;

/*---------------------------------------------------------------------------------*/
typedef struct
{
	/*---- parameters ----*/
	float 	    fmax; // sort of max frequency
	float   	fmin; // sort of min frequency
	float   	gain; // drifter output is bound in [-gain, +gain]

} DrifterParams_t;

/*----------------------------------------------------------------------------------*/
void 	Drifter_init(Drifter_t *d);
void 	Drifter_params_save(const Drifter_t *d, DrifterParams_t *params);
void 	Drifter_params_set(const DrifterParams_t *params, Drifter_t *d);
float 	Drifter_nextSample(Drifter_t *d);

#ifdef __cplusplus
 }
#endif

/************************************************************************************/
#endif
