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
#define invalidDesignator 0b00000001

//Structure
typedef struct CommsPacketStruct {
	// where the packet goes to. GS, Pi, or WTC. Reject if not recognized.
	uint8_t designator;			//001 byte
	// time stamp, serialization of the packets (packet ID)
	uint8_t miscInteger[4];		//004 bytes
	uint8_t data[123];			//123 bytes
	// use EOF(ASCII#26) to mark end of a file transmission

	//to monitor ongoing transmission
	uint8_t flag;

} CommsPacketStruct;

extern CommsPacketStruct * commsPacketStruct;

uint8_t initCommsPacketStruct(/*x,y,z*/) {
	//missing parameter (data from ground)
	//commsPacketStruct->designator = x;
	//commsPacketStruct->miscInteger = y;
	//commsPacketStruct->data = z;
	//commsPacketStruct->flag;

	return 0;
}

uint8_t isValid_designator() {

	switch (commsPacketStruct->designator) {
	case (designatorWTC):
		//go to WTC transmission code
		break;
	case (designatorPi1):
		//go to Pi1 transmission code
		break;
	case (designatorPi2):
		//go to Pi2 transmission code
		break;
	default:
		//ask to re-send packet
		return invalidDesignator;
	}

	return 0;
}

void commsLoop();
void commsGround();
void groundPis();

#endif /* STATEMACHINE_COMMS_H_ */
