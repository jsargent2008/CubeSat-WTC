/*
 * SS_Pi_Comms.h
 *
 *  Created on: May 29, 2018
 *      Author: Administrator
 */

#ifndef PI_CONTROL_SS_PI_COMMS_H_
#define PI_CONTROL_SS_PI_COMMS_H_

//includes
#include "main.h"
#include "string.h"
#include "usart.h"
#include "UART_IRQ/UART_IRQ.h"

//defines
#define FLAG_WRONG_PI 1
#define FLAG_WRONG_TIME 2
#define FLAG_ERR_START 3
#define FLAG_ERR_ACK 4
#define FLAG_ERR_TRANSMISSION 5

/*
 * FILE SHOULD CONTAIN FUNCTIONS ONLY FOR SURFSAT
 */

//function prototypes
uint8_t SS_GndToPi(uint8_t pi, uint8_t *packet, uint8_t timeStart, uint8_t timeStop);

#endif /* PI_CONTROL_SS_PI_COMMS_H_ */
