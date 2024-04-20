/*
 * interface.c
 *
 *  Created on: Nov 14, 2023
 *      Author: Xavier Halgand
 */
/*------------------------------------------------------------------------------------------------------------------*/
#include "interface.h"

#include <stdint.h>
#include <math.h>

#include "usbh_midi_XH.h"
#include "usb_host.h"
#include "stm32h747i_discovery.h"
#include "stm32_lcd.h"
#include "openamp.h"
#include "constants.h"
#include "binn.h"
#include "soundGen.h"
#include "stm32h747i_discovery_qspi.h"

/*------------------------ Private macro ---------------------------------------------------------------------------*/
#define RPMSG_SERVICE_NAME 			"M4_M7_communication"
#define RX_BUFF_SIZE 				64 /* USB MIDI buffer : max received data 64 bytes */
#define CYC_MAX						(((float)AUDIO_BUFFER_SIZE / 8.0f) * ((float)FREQ_CM7 / (float)SAMPLERATE))

/*--------- for QSPI Flash --------------------*/
#define SUBSECTOR_SIZE				8192
#define MAX_PATCH_SIZE				1024 /* also defined in constants.h */
#define PATCH_MEMORY_START_ADDRESS	0x0

enum MenuPage
{
	BOTTOM, VOL_PG, INST_PG, LOAD_PG, SAVE_PG, TOP,
};

/*------------------------------------------------------------------------------------------------------------------*/
extern ApplicationTypeDef Appli_state;
extern USBH_HandleTypeDef hUsbHostHS;

/*------------------------------------------------------------------------------------------------------------------*/
static int rpmsg_recv_callback(struct rpmsg_endpoint *ept, void *data, size_t len, uint32_t src, void *priv);
static void Process_ReceivedMidiDatas(void);
static void midipacket_print(midi_package_t pack);
static int32_t write_patch_to_memory(SynthPatch_t *patch);
static void write_initPatch_to_sector8Kbuffer(SynthPatch_t *patch);

/* -----------------------------------------------------------------------------------------------------------------*/
HSEM_TypeDef *HSEM_DEBUG = HSEM;

/*-------------------------------------- Private variables ---------------------------------------------------------*/
static uint8_t MIDI_RX_Buffer[RX_BUFF_SIZE]; // MIDI reception buffer
static uint32_t oldtick, newtick;
//static uint32_t oldtick2, newtick2;
static volatile int message_received;
//static volatile uint32_t received_number;
static struct rpmsg_endpoint rp_endpoint;
static char string_message[100];
static char *blank_message = "                              ";
static uint8_t sector8Kbuffer[SUBSECTOR_SIZE];
static SynthPatch_t *patch;
static char *strg;
static uint8_t messageBuffer[1024];
static volatile bool SEV_received;

static volatile uint32_t JoyPinPressed = 0;
static volatile uint32_t Joy_State;
static volatile bool joyOn;
static volatile bool pushbuttonON;

static uint8_t menu_page;

/* message buffers pointers in SRAM4 */
volatile uint8_t *buf_cm4_to_cm7 = (void*) BUFF_CM4_TO_CM7_ADDR;
volatile uint8_t *buf_cm7_to_cm4 = (void*) BUFF_CM7_TO_CM4_ADDR;
volatile ScreenDatas_t *scr_datas = (void*) BUFF2_CM7_TO_CM4_ADDR;

/*------------------------------------------------------------------------------------------------------------------*/
void openamp_init(void)
{
	SEV_received = false;

	/* Initialize the mailbox use notify the other core on new message */
	MAILBOX_Init();

	/* Initialize OpenAmp and libmetal libraries */
	if (MX_OPENAMP_Init(RPMSG_REMOTE, NULL) != HAL_OK)
		Error_Handler();

	/* create an endpoint for rmpsg communication */
	int32_t status = 0;
	status = OPENAMP_create_endpoint(&rp_endpoint, RPMSG_SERVICE_NAME, RPMSG_ADDR_ANY, rpmsg_recv_callback, NULL);
	if (status < 0)
	{
		Error_Handler();
	}

	/* Clear message buffers */
	memset((void*) buf_cm4_to_cm7, 0x00, MAX_PATCH_SIZE);
	memset((void*) buf_cm7_to_cm4, 0x00, MAX_PATCH_SIZE);
	memset((void*) scr_datas, 0x00, MAX_BUFF2_SIZE);
	message_received = 0;
	SEV_received = false;
	message_received = 0;
	JoyPinPressed = 0;
	Joy_State = JOY_NONE;
	joyOn = false;
	pushbuttonON = false;
	menu_page = VOL_PG;

}
/*----------------------------------------------------------------------------------------------------------------*/
static int rpmsg_recv_callback(struct rpmsg_endpoint *ept, void *data, size_t len, uint32_t src, void *priv)
{
	memcpy(messageBuffer, data, len); /* copy data to message buffer */
	message_received = 1;
	return 0;
}

/*----------------------------------------------------------------------------------------------------------------*/
void refresh_screen_infos(volatile ScreenDatas_t *datas)
{
	UTIL_LCD_SetFont(&Font12);

	if (datas->instrument_par == Desynkator)
		UTIL_LCD_DisplayStringAt(123, 203, (uint8_t*) "x", LEFT_MODE);
	else
		UTIL_LCD_DisplayStringAt(123, 203, (uint8_t*) " ", LEFT_MODE);

	if (datas->instrument_par == Dekrispator)
		UTIL_LCD_DisplayStringAt(123, 167, (uint8_t*) "x", LEFT_MODE);
	else
		UTIL_LCD_DisplayStringAt(123, 167, (uint8_t*) " ", LEFT_MODE);

	if (datas->instrument_par == Drumzator)
		UTIL_LCD_DisplayStringAt(123, 238, (uint8_t*) "x", LEFT_MODE);
	else
		UTIL_LCD_DisplayStringAt(123, 238, (uint8_t*) " ", LEFT_MODE);

	UTIL_LCD_SetFont(&Font20);

	if (datas->delayON_par)
		UTIL_LCD_DisplayStringAt(63, 58, (uint8_t*) "X", LEFT_MODE);
	else
		UTIL_LCD_DisplayStringAt(63, 58, (uint8_t*) " ", LEFT_MODE);

	if (datas->phaserON_par)
		UTIL_LCD_DisplayStringAt(142, 58, (uint8_t*) "X", LEFT_MODE);
	else
		UTIL_LCD_DisplayStringAt(142, 58, (uint8_t*) " ", LEFT_MODE);

	if (datas->chorusON_par)
		UTIL_LCD_DisplayStringAt(223, 58, (uint8_t*) "X", LEFT_MODE);
	else
		UTIL_LCD_DisplayStringAt(223, 58, (uint8_t*) " ", LEFT_MODE);

	if (datas->autoFilterON_par)
		UTIL_LCD_DisplayStringAt(303, 58, (uint8_t*) "X", LEFT_MODE);
	else
		UTIL_LCD_DisplayStringAt(303, 58, (uint8_t*) " ", LEFT_MODE);

	if (datas->sequencerIsOn_par)
		UTIL_LCD_DisplayStringAt(56, 428, (uint8_t*) "X", LEFT_MODE);
	else
		UTIL_LCD_DisplayStringAt(56, 428, (uint8_t*) " ", LEFT_MODE);

	if (datas->holes_par)
		UTIL_LCD_DisplayStringAt(273, 428, (uint8_t*) "X", LEFT_MODE);
	else
		UTIL_LCD_DisplayStringAt(273, 428, (uint8_t*) " ", LEFT_MODE);

	if (datas->move_par)
		UTIL_LCD_DisplayStringAt(346, 428, (uint8_t*) "X", LEFT_MODE);
	else
		UTIL_LCD_DisplayStringAt(346, 428, (uint8_t*) " ", LEFT_MODE);

	/* Tempo */
	sprintf(string_message, "%3u", (uint16_t) roundf(datas->tempo_par));
	UTIL_LCD_DisplayStringAt(113, 428, (uint8_t*) string_message, LEFT_MODE);

	/* Sequence length */
	sprintf(string_message, "%2u", datas->seq_length_par);
	UTIL_LCD_DisplayStringAt(191, 428, (uint8_t*) string_message, LEFT_MODE);

	/* Sound */
	sprintf(string_message, "%2u", datas->sound_par);
	UTIL_LCD_DisplayStringAt(600, 428, (uint8_t*) string_message, LEFT_MODE);

	/* Memory number / patch location */
	sprintf(string_message, "%2u", 1 + datas->memory_loc_par);
	UTIL_LCD_DisplayStringAt(732, 428, (uint8_t*) string_message, LEFT_MODE);

}
/*----------------------------------------------------------------------------------------------------------------*/
void CM7_SEV_signal(void)
{
	SEV_received = true;
}

/*----------------------------------------------------------------------------------------------------------------*/
int32_t write_patch_to_memory(SynthPatch_t *patch)
{
	//uint32_t sectorAddress = PATCH_MEMORY_START_ADDRESS * (1 + (patch->memory_location) / 8); /* Find address of 8k sector in which patch will be written */
	uint32_t sectorAddress = PATCH_MEMORY_START_ADDRESS + SUBSECTOR_SIZE * ((patch->memory_location) / 8); /* Find address of 8k sector in which patch will be written */

	if (BSP_QSPI_Read(0, sector8Kbuffer, sectorAddress, SUBSECTOR_SIZE) != BSP_ERROR_NONE) /* read this 8k sector to buffer before erasing */
	{
		printf("Read error !\n");
		return BSP_ERROR_COMPONENT_FAILURE;
	}

	uint32_t patchAddress = (patch->memory_location % 8) * MAX_PATCH_SIZE; /* Find relative address of patch in the sector */
	memcpy(&sector8Kbuffer[patchAddress], patch, sizeof(*patch)); /* copy patch to buffer */

	if (BSP_QSPI_EraseBlock(0, sectorAddress, BSP_QSPI_ERASE_8K) != BSP_ERROR_NONE) /* erase sector */
	{
		printf("Erase error !\n");
		return BSP_ERROR_COMPONENT_FAILURE;
	}

	if (BSP_QSPI_Write(0, sector8Kbuffer, sectorAddress, SUBSECTOR_SIZE) != BSP_ERROR_NONE)/* write buffer with new patch to qspi flash */
	{
		printf("Write error !\n");
		return BSP_ERROR_COMPONENT_FAILURE;
	}
	return BSP_ERROR_NONE;
}

/*----------------------------------------------------------------------------------------------------------------*/
void write_initPatch_to_sector8Kbuffer(SynthPatch_t *patch) /* Fill sector8Kbuffer with 8 times the same patch  */
{
	for (int i = 0; i < SUBSECTOR_SIZE; i++) /* erase sector buffer */
	{
		sector8Kbuffer[i] = 0;
	}
	uint32_t patchAddress;
	for (int j = 0; j < 8; j++) /* 8 patches per buffer */
	{
		patchAddress = j * MAX_PATCH_SIZE; /* Find relative address of patch in the sector */
		memcpy(&sector8Kbuffer[patchAddress], patch, sizeof(*patch)); /* copy patch to buffer */
	}
}
/*----------------------------------------------------------------------------------------------------------------*/
void midipacket_sendToCM7(midi_package_t packet)
{
	int32_t status = 0;
	status = OPENAMP_send(&rp_endpoint, &packet, sizeof(packet));
	if (status < 0)
	{
		Error_Handler();
	}
}

/*------------------------------------------------------------------------------------------------*/
void BSP_PB_Callback(Button_TypeDef Button)
{
	pushbuttonON = true;
}
/*------------------------------------------------------------------------------------------------*/
void BSP_JOY_Callback(JOY_TypeDef JOY, uint32_t JoyPin)
{
	JoyPinPressed = JoyPin;
	joyOn = !joyOn;
}

/*------------------------------------------------------------------------------------------------*/
void LCD_DisplayMenuPage(const uint8_t *page_p)
{
	UTIL_LCD_DisplayStringAt(201, 297, (uint8_t*) blank_message, LEFT_MODE); // Erase message window

	switch (*page_p)
	{
	case VOL_PG:
		UTIL_LCD_DisplayStringAt(201, 297, (uint8_t*) "VOLUME page !", LEFT_MODE);
		break;

	case INST_PG:
		UTIL_LCD_DisplayStringAt(201, 297, (uint8_t*) "INSTRUMENT page !", LEFT_MODE);
		break;

	case LOAD_PG:
		UTIL_LCD_DisplayStringAt(201, 297, (uint8_t*) "LOAD PATCH page !", LEFT_MODE);
		break;

	case SAVE_PG:
		UTIL_LCD_DisplayStringAt(201, 297, (uint8_t*) "SAVE PATCH page !", LEFT_MODE);
		break;

	default:
		break;
	}
}

/*------------------------------------------------------------------------------------------------*/
void volume_page_action(uint8_t *page_p, uint32_t joy)
{
	midi_package_t packet;

	switch (joy)
	{
	case JOY_LEFT:
		*page_p = INST_PG;
		printf("Menu : Instru\n");
		LCD_DisplayMenuPage(page_p);
		break;

	case JOY_RIGHT:
		*page_p = LOAD_PG;
		printf("Menu : LOAD\n");
		LCD_DisplayMenuPage(page_p);
		break;

	case JOY_UP:
		printf("Augmenter volume\n");
		packet.ALL = VOL_INC_CMD;
		midipacket_sendToCM7(packet);
		break;

	case JOY_DOWN:
		printf("Baisser volume\n");
		packet.ALL = VOL_DEC_CMD;
		midipacket_sendToCM7(packet);
		break;

	case JOY_SEL:

		break;

	default:
		break;

	}
}

/*------------------------------------------------------------------------------------------------*/
void instru_page_action(uint8_t *page_p, uint32_t joy)
{
	midi_package_t packet;

	switch (joy)
	{
	case JOY_LEFT:
		*page_p = SAVE_PG;
		printf("Menu : SAVE\n");
		LCD_DisplayMenuPage(page_p);
		break;

	case JOY_RIGHT:
		*page_p = VOL_PG;
		printf("Menu : VOL\n");
		LCD_DisplayMenuPage(page_p);
		break;

	case JOY_UP:
		printf("Instru suivant\n");
		packet.ALL = CHG_INSTR_CMD;
		midipacket_sendToCM7(packet);
		break;

	case JOY_DOWN:
		printf("Instru precedent\n");
		break;

	case JOY_SEL:

		break;

	default:
		break;

	}
}

/*------------------------------------------------------------------------------------------------*/
void load_page_action(uint8_t *page_p, uint32_t joy)
{

	midi_package_t packet;

	switch (joy)
	{
	case JOY_LEFT:
		*page_p = VOL_PG;
		printf("Menu : VOL\n");
		LCD_DisplayMenuPage(page_p);
		break;

	case JOY_RIGHT:
		*page_p = SAVE_PG;
		printf("Menu : SAVE\n");
		LCD_DisplayMenuPage(page_p);
		break;

	case JOY_UP:
		printf("Memoire suivante\n");
		packet.ALL = NEXT_LOC_CMD;
		midipacket_sendToCM7(packet);
		break;

	case JOY_DOWN:
		printf("Memoire precedente\n");
		packet.ALL = PREV_LOC_CMD;
		midipacket_sendToCM7(packet);
		break;

	case JOY_SEL:
		printf("Load patch.\n");
		packet.ALL = LOAD_CMD;
		midipacket_sendToCM7(packet);
		break;

	default:
		break;

	}
}

/*------------------------------------------------------------------------------------------------*/
void save_page_action(uint8_t *page_p, uint32_t joy)
{

	midi_package_t packet;

	switch (joy)
	{
	case JOY_LEFT:
		*page_p = LOAD_PG;
		printf("Menu : LOAD\n");
		LCD_DisplayMenuPage(page_p);
		break;

	case JOY_RIGHT:
		*page_p = INST_PG;
		printf("Menu : Instru\n");
		LCD_DisplayMenuPage(page_p);
		break;

	case JOY_UP:
		printf("Memoire suivante\n");
		packet.ALL = NEXT_LOC_CMD;
		midipacket_sendToCM7(packet);
		break;

	case JOY_DOWN:
		printf("Memoire precedente\n");
		packet.ALL = PREV_LOC_CMD;
		midipacket_sendToCM7(packet);
		break;

	case JOY_SEL:
		printf("Save patch.\n");
		packet.ALL = SAVE_CMD;
		midipacket_sendToCM7(packet);
		break;

	default:
		break;

	}
}

/*------------------------------------------------------------------------------------------------*/
void buttonAction(uint8_t *page_p)
{
	midi_package_t pack;

	printf("Button pushed !\n");
	pack.ALL = TOG_FREEZE_CMD;
	midipacket_sendToCM7(pack);
}

/*------------------------------------------------------------------------------------------------*/
void joystickAction(uint8_t *page_p, uint32_t joy)
{
	switch (*page_p)
	{
	case VOL_PG:
		volume_page_action(page_p, joy);
		break;

	case INST_PG:
		instru_page_action(page_p, joy);
		break;

	case LOAD_PG:
		load_page_action(page_p, joy);
		break;

	case SAVE_PG:
		save_page_action(page_p, joy);
		break;

	default:
		break;
	}
}
/*------------------------------------------------------------------------------------------------*/
void Application_Process(void) // called in main() loop (main_cm4.c)
{
	midi_package_t pack;

	/* Is there a new patch written by CM7 in the shared buffer ? */
	if (SEV_received)
	{
		printf("SEV signal from CM7 received !\n");
		patch = (SynthPatch_t*) buf_cm7_to_cm4;
		SEV_received = false;
	}

	/*------- read wake-up button ---------------*/
	if (pushbuttonON)
	{
		buttonAction(&menu_page);
		pushbuttonON = false; // Button action done
	}

	/*------- read joystick ---------------*/
	if (joyOn) /* if joystick is pressed and not released */
	{
		joystickAction(&menu_page, JoyPinPressed);
		JoyPinPressed = 0; /*  joystick action done */
	}

	/* Check for CM7 messages (openAMP) */
	if (message_received == 0)
	{
		OPENAMP_check_for_message();
	}
	if (message_received)
	{
		uint16_t loc;
		uint8_t cmd;
		uint32_t sectorAddress;

		cmd = binn_object_uint8(messageBuffer, "cmd");

		switch (cmd)
		{

		case 'D': /* request for loading a patch */
			loc = binn_object_uint16(messageBuffer, "location");
			uint32_t patchAddress = PATCH_MEMORY_START_ADDRESS + MAX_PATCH_SIZE * loc; /* Find address of memory in which patch will be read */

			if (BSP_QSPI_Read(0, (uint8_t*) buf_cm4_to_cm7, patchAddress, sizeof(*patch)) != BSP_ERROR_NONE) /* read this patch to buffer */
			{
				printf("Read error !\n");
				//return BSP_ERROR_COMPONENT_FAILURE;
			}
			else
			{
				/* inform CM7 that a patch is ready in shared "buf_cm4_to_cm7" buffer */
				//asm("sev");
				pack.ALL = LOAD_PATCH_CMD;
				midipacket_sendToCM7(pack);
				printf("Patch # %u loaded !\n", loc + 1); /* hope it's been loaded ! */
				sprintf(string_message, "Patch # %u loaded !", loc + 1);
				UTIL_LCD_DisplayStringAt(201, 297, (uint8_t*) blank_message, LEFT_MODE); // Erase message window
				UTIL_LCD_DisplayStringAt(201, 297, (uint8_t*) string_message, LEFT_MODE);
			}
			break;

		case 'L': /* print current patch location */
			loc = binn_object_uint16(messageBuffer, "location");
			printf("Current patch location : %u\n", loc + 1);
			sprintf(string_message, "%2u", loc + 1);
			UTIL_LCD_DisplayStringAt(732, 428, (uint8_t*) string_message, LEFT_MODE);
			break;

		case 'P': /* save patch */
			if (patch == NULL)
				printf("patch = NULL !!!");
			else
			{
				if (write_patch_to_memory(patch) == BSP_ERROR_NONE)
				{
					printf("Patch saved in memory # %u !\n", 1 + patch->memory_location);
					sprintf(string_message, "Patch saved in memory # %u !  ", 1 + patch->memory_location);
					UTIL_LCD_DisplayStringAt(201, 297, (uint8_t*) string_message, LEFT_MODE);
					printf("Size of patch is : %d bytes.\n", sizeof(*patch));
				}
			}
			break;

		case 'R': /* request for erase memory */
			printf("Erase all patches ?\n");
			UTIL_LCD_DisplayStringAt(201, 297, (uint8_t*) blank_message, LEFT_MODE); // Erase message window
			UTIL_LCD_DisplayStringAt(201, 297, (uint8_t*) "Erase all patches ?", LEFT_MODE);
			break;

		case 'E': /* erase memory */
			UTIL_LCD_DisplayStringAt(201, 297, (uint8_t*) blank_message, LEFT_MODE);
			if (BSP_QSPI_EraseBlock(0, PATCH_MEMORY_START_ADDRESS, BSP_QSPI_ERASE_128K) == BSP_ERROR_NONE)
			{
				printf("All patches erased ! \n");
				UTIL_LCD_DisplayStringAt(201, 297, (uint8_t*) blank_message, LEFT_MODE); // Erase message window
				UTIL_LCD_DisplayStringAt(201, 297, (uint8_t*) "All patches erased !", LEFT_MODE);
				//patch = binn_object_blob(messageBuffer, "patch", &received_data_len);
				//printf("Size of Init patch is : %d bytes.\n", sizeof(*patch));
				write_initPatch_to_sector8Kbuffer(patch);

				for (int i = 0; i < 4; i++)
				{
					sectorAddress = PATCH_MEMORY_START_ADDRESS + SUBSECTOR_SIZE * i;
					if (BSP_QSPI_Write(0, sector8Kbuffer, sectorAddress, SUBSECTOR_SIZE) != BSP_ERROR_NONE)/* write buffer with 8 init patches to qspi flash */
					{
						printf("Write error !\n");
					}
				}
				printf("Memory initialized !\n");
			}
			else
				printf("Memory can't be erased ! \n");

			break;

		case 'S': /* print any string */
			UTIL_LCD_DisplayStringAt(201, 297, (uint8_t*) blank_message, LEFT_MODE); // Erase message window
			strg = binn_object_str(messageBuffer, "string");
			UTIL_LCD_DisplayStringAt(201, 297, (uint8_t*) strg, LEFT_MODE);
			printf("\n");
			printf(strg);
			printf("\n");
			free(strg);
			break;

		case 'X': /* print CPU M7 load */
			uint32_t received_number = binn_object_uint32(messageBuffer, "number");
			uint32_t occupation_cm7 = (uint32_t) roundf((100 * (float) received_number / CYC_MAX));

			//printf("Nombre de cycles moyen de CM7 = %lu \n", received_number);
			//printf("Taux d'occupation moyen CM7 = %lu %% \n", occupation_cm7);

			//sprintf(string_message, "Average CPU load (M7) = %lu%%   ", occupation_cm7);
			//UTIL_LCD_DisplayStringAt(20, 220, (uint8_t*) string_message, LEFT_MODE);

			sprintf(string_message, "%2lu%%", occupation_cm7);
			UTIL_LCD_DisplayStringAt(728, 60, (uint8_t*) string_message, LEFT_MODE);
			break;

		case 'C':
			refresh_screen_infos(scr_datas);
			break;

		case 'B': // clear message
			UTIL_LCD_DisplayStringAt(201, 297, (uint8_t*) blank_message, LEFT_MODE);
			break;

		default:
			printf("openAMP message received !\n");
			break;
		}

		message_received = 0;
	}

	if (Appli_state == APPLICATION_IDLE)
	{
		UTIL_LCD_DisplayStringAt(610, 58, (uint8_t*) "-", LEFT_MODE);
	}

	if (Appli_state == APPLICATION_RUNNING) /* Check for MIDI messages (if USB MIDI controller connected) */
	{
		/* start a new MIDI reception not faster than 1 per ms */
		newtick = HAL_GetTick();
		if (newtick != oldtick)
		{
			USBH_MIDI_Receive(&hUsbHostHS, MIDI_RX_Buffer, RX_BUFF_SIZE);
			oldtick = newtick;
		}
	}

	if (Appli_state == APPLICATION_READY)
	{
		BSP_LED_On(LED_GREEN);
		UTIL_LCD_DisplayStringAt(610, 58, (uint8_t*) "X", LEFT_MODE);
		Appli_state = APPLICATION_RUNNING;
	}

	if (Appli_state == APPLICATION_DISCONNECT)
	{
		BSP_LED_Off(LED_GREEN);
		UTIL_LCD_DisplayStringAt(610, 58, (uint8_t*) "-", LEFT_MODE);
		Appli_state = APPLICATION_IDLE;
		USBH_MIDI_Stop(&hUsbHostHS);
	}

//	newtick2 = HAL_GetTick();
//	if ((newtick2 - oldtick2) >= 2000)
//	{
//		printf("CM4 is still alive ! \n");
//		oldtick2 = newtick2;
//	}
}

/*-----------------------------------------------------------------------------*/
/**
 * @brief  MIDI data receive callback. Redefinition of _weak function defined in usbh_midi_XH.c
 * @param  phost: Host handle
 * @retval None
 */
void USBH_MIDI_ReceiveCallback(USBH_HandleTypeDef *phost)
{
	BSP_LED_On(LED_BLUE);
	Process_ReceivedMidiDatas();
	BSP_LED_Off(LED_BLUE);
}

/*-----------------------------------------------------------------------------*/
void Process_ReceivedMidiDatas(void)
{
	uint16_t numberOfPackets;
	uint8_t *ptr = MIDI_RX_Buffer;
	midi_package_t pack;

	numberOfPackets = USBH_MIDI_GetLastReceivedDataSize(&hUsbHostHS) / 4; //each USB midi package is 4 bytes long

	while (numberOfPackets--)
	{
		pack.cin_cable = *ptr;
		ptr++;
		pack.evnt0 = *ptr;
		ptr++;
		pack.evnt1 = *ptr;
		ptr++;
		pack.evnt2 = *ptr;
		ptr++;

		if (pack.ALL != 0) // if incoming midi message...
		{
			midipacket_sendToCM7(pack);
			midipacket_print(pack);
		}
	}
}
/*------------------------------------------------------------------------------------------------*/
void midipacket_print(midi_package_t pack) //cf. Teensy-MIDI-monitor
{
	uint8_t type = pack.cin;
	uint8_t channel = 1 + pack.chn;
	uint8_t data1 = pack.evnt1;
	uint8_t data2 = pack.evnt2;

	switch (type)
	{
	case NoteOff: // 0x8
		printf("Note Off, ch= %d", channel);
		printf(", note= %d", data1);
		printf(", velocity= %d", data2);
		printf("\n");
		break;

	case NoteOn: // 0x9
		printf("Note On, ch= %d", channel);
		printf(", note= %d", data1);
		printf(", velocity= %d", data2);
		printf("\n");
		break;

	case ControlChange: // 0xB
		printf("Control Change, ch= %d", channel);
		printf(", control= %d", data1);
		printf(", value= %d", data2);
		printf(", Packet = 0x%08lX", pack.ALL);
		printf("\n");
		break;

	case ProgramChange: // 0xC
		printf("Program Change, ch= %d", channel);
		printf(", program= %d", data1);
		printf("\n");
		break;

	case Aftertouch: // 0xD
		printf("AfterTouch, ch= %d", channel);
		printf(", pressure= %d", data1);
		printf("\n");
		break;

	case PitchBend: // 0xE
		printf("PitchBend, ch= %d", channel);
		printf(", pitch= %d", data1 + data2 * 128);
		printf("\n");
		break;

	case PolyPressure: // 0xA
		printf("PolyKeyPress, ch= %d", channel);
		printf(", note= %d", data1);
		printf(", velocity= %d", data2);
		printf("\n");
		break;

	default:
		printf("Other MIDI packet : %X, %X, %d, %d   \n", pack.cin_cable, pack.evnt0, pack.evnt1, pack.evnt2);

	}
}

//**************************************************************************
//	case midi_SystemExclusive: // 0xF0
//		// Messages larger than usbMIDI's internal buffer are truncated.
//		// To receive large messages, you *must* use the 3-input function
//		// handler.  See InputFunctionsComplete for details.
//		print("SysEx Message // 0xF0: ");
//		printBytes(MIDI1.getSysExArray(), data1 + data2 * 256);
//		printf("\n");
//		break;
//
//	case midi_TimeCodeQuarterFrame: // 0xF1
//		printf("TimeCode // 0xF1, index=");
//		printf(data1 >> 4, DEC);
//		printf(", digit=");
//		printf(data1 & 15, DEC);
//		printf("\n");
//		break;
//
//	case midi_SongPosition: // 0xF2
//		printf("Song Position // 0xF2, beat=");
//		printf(data1 + data2 * 128);
//		printf("\n");
//		break;
//
//	case midi_SongSelect: // 0xF3
//		printf("Sond Select // 0xF3, song=");
//		printf(data1, DEC);
//		printf("\n");
//		break;
//
//	case midi_TuneRequest: // 0xF6
//		println("Tune Request // 0xF6");
//		printf("\n");
//		break;
//
//	case midi_Clock: // 0xF8
//		printf("Clock // 0xF8");
//		printf("\n");
//		break;
//
//	case midi_Start: // 0xFA
//		printf("Start // 0xFA");
//		printf("\n");
//		break;
//
//	case midi_Continue: // 0xFB
//		printf("Continue // 0xFB");
//		printf("\n");
//		break;
//
//	case midi_Stop: // 0xFC
//		printf("Stop // 0xFC");
//		printf("\n");
//		break;
//
//	case midi_ActiveSensing: // 0xFE
//		printf("Actvice Sensing // 0xFE");
//		printf("\n");
//		break;
//
//	case midi_SystemReset: // 0xFF
//		printf("System Reset // 0xFF");
//		printf("\n");
//		break;
//*************************************************************
