/*
 * comms.h
 *
 *  Created on: May 22, 2018
 *      Author: Administrator
 */

#ifndef COMMS_H_
#define COMMS_H_

#include "statemachine.h"

//Defines

//designator byte
#define designatorWTC 0b11111111
#define designatorPi1 0b00000001
#define designatorPi2 0b00000010
//flag types
#define invalidDesignator 0

//Structures
typedef struct CommsRxPacketStruct {
	// where the packet goes to. GS, Pi, or WTC. Reject if not recognized.
	uint8_t designator;			//001 byte
	// time stamp, serialization of the packets (packet ID)
	uint8_t miscInteger[4];		//004 bytes
	uint8_t data[123];			//123 bytes
	// use EOF(ASCII#26) to mark end of a file transmission

	//to monitor ongoing transmission
	uint8_t flag;

} CommsRxPacketStruct;

extern CommsRxPacketStruct * commsRxPacketStruct;

typedef struct CommsTxPacketStruct {
	uint8_t data[128];			//128 bytes
	// use EOF(ASCII#26) to mark end of a file transmission

	//to monitor ongoing transmission
	uint8_t flag;

} CommsTxPacketStruct;

extern CommsTxPacketStruct * commsTxPacketStruct;

void commsLoop(uint8_t* buffer);
void helloGround(uint8_t* buffer);
void commsToGround(uint8_t* buffer);
void commsFromGround(uint8_t* buffer);
void commsToWTC(uint8_t* buffer);
void commsToPis(uint8_t* buffer, uint8_t pi);
void commsFromPis(uint8_t* buffer);


/*
 * helper function prototypes
 */
uint8_t isValid_designator();


#endif /* STATEMACHINE_COMMS_H_ */
