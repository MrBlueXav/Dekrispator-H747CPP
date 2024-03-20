/*
 * interface.h
 *
 *  Created on: Nov 14, 2023
 *      Author: Xavier Halgand
 */
#ifndef APPLICATION_CM7_INTERFACE_H_
#define APPLICATION_CM7_INTERFACE_H_

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------------------------------------------*/

/*-------------------------------- Exported functions  ------------------------------------------------------------*/

void openamp_init(void);
void Application_Process(void);
void CM7_SEV_signal(void);

/*-----------------------------------------------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* APPLICATION_CM7_INTERFACE_H_ */
