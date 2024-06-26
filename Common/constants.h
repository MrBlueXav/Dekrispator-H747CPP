/**
 ******************************************************************************
 * File Name          : constants.h
 * Author			  : Xavier Halgand
 * Date               :	2024
 * Description        : Global defines for Dekrispator
 ******************************************************************************
 */
#ifndef __DEKR_CONSTANTS_H__
#define __DEKR_CONSTANTS_H__

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************************************************/
#define AUDIO_BUFFER_SIZE       1024 /* AUDIO_BUFFER_SIZE (in bytes) must be a multiple of 8   */

#define FREQ_CM7				400000000

#define SAMPLERATE              48000 // Don't modify !

#define Ts						(1.f/SAMPLERATE)  // sample period
#define _2PI                    6.283185307f
#define _PI                    	3.14159265f

#define VOL                     60 // initial output DAC volume
#define MAXVOL                  100 // maximal output DAC volume

#define MIDI_MAX				127.f 	// floating max value
#define MIDI_MAXi				127		// integer max value
#define MIDI_MID_i				64		// integer mid value

#define USE_THE_LCD				1
#define BACKGRND_ADDR			((uint32_t *)0x97E80000) /* address in QSPI Flash for background image  : 0x90000000 + 128MB - 1.5MB */

/***************************************** Special MIDI messages from CM4 for CM7 ************************************************************/
/*****  !!! Little endian encoding !!!    ******/
/* Special user packets */
#define VOL_INC_CMD				0x00000101
#define VOL_DEC_CMD				0x00000201
#define LOAD_PATCH_CMD			0x00000301
#define CHG_INSTR_CMD			0x00000401
#define TOG_FREEZE_CMD			0x00000501

/* True MIDI CC packet, must be same as in MIDI_application.c ! : */
#define NEXT_LOC_CMD			0x7F4BB00B
#define PREV_LOC_CMD			0x7F4AB00B
#define LOAD_CMD				0x7F54B00B
#define SAVE_CMD				0x7F53B00B

/*****************************************************************************************************************/
#define _DTCMRAM_				__attribute__((section(".DTCMRAM_section_bss")))
#define _SDRAM_					__attribute__((section(".sdram_bss")))

#define _ITCMRAM_				__attribute__((section(".itcm_text")))
//#define	_ITCMRAM_
//#define _DTCMRAM_

/******************************************************************************************************************/
#define MAX_PATCH_SIZE			1024	/* Don't modify */
#define LAST_PATCH				31	//Number - 1  of patches that can be stored in QSPI Flash, maximum is 127.
#define MAX_BUFF2_SIZE			1024 /* buffer for screen datas */

/* Align X to 4 bytes */
#define MEM_ALIGN(x)			(((x) + 0x00000003) & ~(0x00000003))

/* Shared RAM between 2 cores is SRAM4 in D3 domain aka SHARED_RAM in linker file */
#define SHD_RAM_START_ADDR                  0x3800C000 /* last 16K of SRAM4 */
#define SHD_RAM_LEN                         0x00003FFF /* 16K */

/* Buffer from CM4 to CM7 */
#define BUFF_CM4_TO_CM7_ADDR                MEM_ALIGN(SHD_RAM_START_ADDR)
#define BUFF_CM4_TO_CM7_LEN                 MEM_ALIGN(MAX_PATCH_SIZE)

/* Buffer from CM7 to CM4 */
#define BUFF_CM7_TO_CM4_ADDR                MEM_ALIGN(BUFF_CM4_TO_CM7_ADDR + BUFF_CM4_TO_CM7_LEN)
#define BUFF_CM7_TO_CM4_LEN                 MEM_ALIGN(MAX_PATCH_SIZE)

/* Buffer 2 from CM7 to CM4 */
#define BUFF2_CM7_TO_CM4_ADDR                MEM_ALIGN(BUFF_CM7_TO_CM4_ADDR + BUFF_CM7_TO_CM4_LEN)
#define BUFF2_CM7_TO_CM4_LEN                 MEM_ALIGN(MAX_BUFF2_SIZE)

/******************************************************************************************************************/
#if defined   (__GNUC__)        /* GNU Compiler */
    #define __ALIGN    __attribute__ ((aligned (4)))
#endif /* __GNUC__ */

/******************************************************************************************************************/

#ifdef __cplusplus
}
#endif

/************************************************************************************/
#endif  /*__DEKR_CONSTANTS_H__ */
