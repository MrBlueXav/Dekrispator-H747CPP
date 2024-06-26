/*
 * drift_3osc.h
 *
 *  Created on: Jan 27, 2024
 *      Author: Xavier Halgand
 */
/*--------------------------------------------------------------------------------------------------------*/
#ifndef DRIFT_3OSC_H_
#define DRIFT_3OSC_H_

#ifdef __cplusplus
 extern "C" {
#endif

/*--------------------------------------------------------------------------------------------------------*/
#include "drifter.h"
#include "osc.h"

/*--------------------------------------------------------------------------------------------------------*/
typedef struct
{
	Oscillator_t 	op1;
	Oscillator_t 	op2;
	Oscillator_t 	op3;
	Drifter_t		d1;
	Drifter_t		d2;
	Drifter_t		d3;
	float			centralFreq;

} DriftingOsc_t;

/*--------------------------------------------------------------------------------------------------------*/
typedef struct
{
	OscillatorParams_t 	op1;
	OscillatorParams_t 	op2;
	OscillatorParams_t 	op3;
	DrifterParams_t		d1;
	DrifterParams_t		d2;
	DrifterParams_t		d3;
	float				centralFreq;

} DriftingOscParams_t;

/*--------------------------------------------------------------------------------------------------------*/
void 	DriftOsc_init (DriftingOsc_t *osc);
void 	DriftOsc_params_save(const DriftingOsc_t *osc, DriftingOscParams_t *params);
void 	DriftOsc_params_set(const DriftingOscParams_t *params, DriftingOsc_t *osc);
void 	DriftOsc_freq_set(DriftingOsc_t *osc, float freq);
float 	DriftOsc_sample_compute (DriftingOsc_t *osc);
void 	DriftOsc_centralFreq_set(DriftingOsc_t *osc, uint8_t);
void	DriftOsc_amp_set(DriftingOsc_t *osc, uint8_t midival);
void	DriftOsc_minFreq_set(DriftingOsc_t *osc, uint8_t midival);
void	DriftOsc_maxFreq_set(DriftingOsc_t *osc, uint8_t midival);

/*--------------------------------------------------------------------------------------------------------*/

#ifdef __cplusplus
 }
#endif

/*--------------------------------------------------------------------------------------------------------*/
#endif /* DRIFT_3OSC_H_ */
