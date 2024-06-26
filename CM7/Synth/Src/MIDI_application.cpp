/*
 * MIDI_application.c
 *
 *  First created on: 6 dec. 2014
 *      Author: Xavier Halgand
 */

/* Includes ------------------------------------------------------------------*/

#include "MIDI_application.h"
#include "main.h"
#include "audio_play.h"
#include "openamp_interface.h"

/*-----------------------------------------------------------------------------*/

uint8_t notes_On[128] _DTCMRAM_;
int8_t notesCount = 0; // number of notes on (keys pressed)
int8_t currentNote _DTCMRAM_;
int8_t velocity _DTCMRAM_;

extern bool g_sequencerIsOn;

/*-----------------------------------------------------------------------------*/
void Do_____nothing(uint8_t val)
{
} /* for ControlFunctionsTable[] */

/*------------------------------MIDI CC implementation----------------------------------------*/
/* Verify, when modified, if a MIDI code has to be changed in constants.h !!!  */
void (*const ControlChangeFunctionsTable[128])(uint8_t val) =
{	Do_____nothing, /* 0 */
	VibratoAmp_set, /* 1    	"Modulation Wheel" 	*/
	DelayWet_set,
	seq_tempo_set,
	seq_freqMax_set, /* 4		"Foot Pedal"		*/
	seq_scale_set, /* 5 */
	Sound_set,
	Volume_set, /* 7 		"Volume" 			*/
	Filter1Freq_set,
	Filter1Res_set,
	Do_____nothing, /* 10 		"Pan"  				*/
	Reverb_length_set, /* 11		"Expression"  		*/
	Filter1Drive_set,
	Do_____nothing,
	Delay_time_set,
	DelayFeedback_set, /* 15 */
	VibratoAmp_set,
	VibratoFreq_set,
	ChorusRate_set,
	ChorusDelay_set,
	ChorusSweep_set, /* 20 */
	ChorusFeedback_set,
	ChorusSecondRate_set,
	Delay_switch,
	Phaser_switch,
	seq_switchMute, /* 25 */
	seq_switchMovingSeq,
	Filter_Random_switch,
	Chorus_switch,
	seq_length_dec,
	seq_length_inc, /* 30 */
	Sequencer_toggle,
	Do_____nothing,
	seq_transpM2,
	seq_transpP2,
	seq_transpM7, /* 35 */
	seq_transpP7,
	seq_transpM1,
	seq_transpP1,
	seq_new_seq,
	seq_tempo_half, /* 40 */
	seq_tempo_double,
	seq_gateTime_set,
	AttTime_set,
	metro_tempo_set,
	metro2_tempo_set, /* 45 */
	metro3_tempo_set,
	Do_____nothing,
	Do_____nothing,
	Do_____nothing,
	DecTime_set, /* 50 */
	SustLevel_set,
	RelTime_set,
	Filter1Freq_set,
	Filter1Res_set,
	Filter1Drive_set, /* 55 */
	Filter1Type_set,
	AmpLFO_amp_set,
	AmpLFO_freq_set,
	DriftOsc1_amp_set,
	DriftOsc1_minFreq_set, /* 60 */
	DriftOsc1_maxFreq_set,
	DriftOsc1_centralFreq_set,
	SynthOut_amp_set,
	Do_____nothing, /*  64 			"Damper pedal" 		*/
	Filt1LFO_amp_set, /* 65 */
	Filt1LFO_freq_set,
	DemoMode_toggle,
	Synth_reset,
	Sequencer_toggle,
	Freeze_toggle, /* 70 */
	metro1_proba_set,
	metro2_proba_set,
	metro3_proba_set,
	Memory_dec,
	Memory_inc, /* 75 */
	RandSound1,
	RandSound2,
	Desynkator_toggle,
	metro_reset_rq,
	Memory_valid, /* 80 */
	MagicFX,
	MagicPatch,
	Soundpatch_save,
	Soundpatch_load,
	FM_OP1_freq_set, /* 85 */
	FM_OP2_freq_set,
	FM_OP3_freq_set,
	FM_OP4_freq_set,
	Phaser_Wet_set,
	Filter2Freq_set, /* 90 */
	Filter2Res_set,
	Filter2Drive_set,
	Filter2Type_set,
	FM_OP1_modInd_set,
	FM_OP2_modInd_set, /* 95 */
	FM_OP3_modInd_set,
	FM_OP4_modInd_set,
	Memory_erase,
	Do_____nothing,
	Do_____nothing, /* 100 */
	Do_____nothing,
	Phaser_Rate_set,
	Phaser_Feedback_set,
	Do_____nothing,
	Filt2LFO_amp_set, /* 105 */
	Filt2LFO_freq_set,
	Do_____nothing,
	FM_OP2_freqMul_inc,
	FM_OP3_freqMul_inc,
	FM_OP4_freqMul_inc, /* 110 */
	Do_____nothing,
	Do_____nothing,
	Do_____nothing,
	Do_____nothing,
	Do_____nothing, /* 115 */
	Do_____nothing,
	FM_OP2_freqMul_dec,
	FM_OP3_freqMul_dec,
	FM_OP4_freqMul_dec,
	Do_____nothing, /* 120 */
	Do_____nothing,
	Do_____nothing,
	Do_____nothing,
	Do_____nothing,
	Do_____nothing, /* 125 */
	Do_____nothing,
	Do_____nothing /* 127 END */

};

/*-----------------------------------------------------------------------------*/
void Reset_notes_On(void)
{
	notesCount = 0;
	for (uint8_t i = 0; i < 128; i++)
		notes_On[i] = 0;
}

/*-----------------------------------------------------------------------------*/
void ProcessReceivedMidiDatas(midi_package_t pack)
{
	if (g_sequencerIsOn == false)
	{
		if ((pack.evnt0 & 0xF0) == 0x80) // Note off ? -------------------------------
		{
			uint8_t noteOff = pack.evnt1;
			notes_On[noteOff] = 0;
			notesCount--;
			if (notesCount <= 0) // no more keys pressed
			{
				ADSRkeyOFF();
				notesCount = 0;
			}
			else // some keys still pressed... (legato)
			{
				if ((noteOff - LOWEST_NOTE) == currentNote) // then let sound the lowest key pressed
				{
					uint8_t i;
					for (i = 0; i < 128; i++)
					{
						if (notes_On[i] == 1) // find the lowest key pressed
							break;
					}
					currentNote = i - LOWEST_NOTE; // conversion for notesFreq[]
				}
			}
		}
		else if ((pack.evnt0 & 0xF0) == 0x90) // Note on ----------------------------
		{
			uint8_t noteOn = pack.evnt1;
			velocity = pack.evnt2;
			if (velocity > 0) // True note on !
			{
				if (noteOn < LOWEST_NOTE) // filtering notes
				{
					currentNote = 0;
				}
				else
				{
					currentNote = noteOn - LOWEST_NOTE; // conversion for notesFreq[]
				}

				ADSRkeyON();
				notesCount++;
				notes_On[noteOn] = 1;
			}
			else
			{
				// ---------  Sometimes Note On with zero velocity means Note Off !
				notes_On[noteOn] = 0;
				notesCount--;
				if (notesCount <= 0)
				{
					ADSRkeyOFF();
					notesCount = 0;
				}
				else
				{
					if ((noteOn - LOWEST_NOTE) == currentNote)
					{
						uint8_t i;
						for (i = 0; i < 128; i++)
						{
							if (notes_On[i] == 1) // find the lowest key pressed
								break;
						}
						currentNote = i - LOWEST_NOTE; // conversion for notesFreq[]
					}
				}
			}
		}
		else if ((pack.evnt0 & 0xF0) == 0xA0) // Aftertouch
		{
			// Filter1Res_set(pack.evnt2);
		}
		else if ((pack.evnt0 & 0xF0) == 0xE0) // Pitch Bend
		{
			// int16_t pitchBend = ((pack.evnt1 << 7) + pack.evnt2) - 0x2000;
		}
	}

	/*------------------------------------------------------------------------------------------*/

	/* If incoming midi message is a Control Change... */
	if ((pack.evnt0 & 0xF0) == 0xB0)
	{
		ControlChangeFunctionsTable[pack.evnt1](pack.evnt2);
	}

	/* Joystick, button and M4 commands :  */
	else if (pack.ALL == VOL_INC_CMD)
	{
		incVol();
	}
	else if (pack.ALL == VOL_DEC_CMD)
	{
		decVol();
	}
	else if (pack.ALL == LOAD_PATCH_CMD)
	{
		load_patch_cmd();
	}
	else if (pack.ALL == CHG_INSTR_CMD)
	{
		change_instru_cmd();
	}
	else if (pack.ALL == TOG_FREEZE_CMD)
	{
		Freeze_toggle(MIDI_MAXi);
	}
}

/*-----------------------------------------------------------------------------*/
