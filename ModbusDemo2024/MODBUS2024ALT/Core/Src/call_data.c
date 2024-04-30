/*
 * call_data.c
 *
 *  Created on: Apr 29, 2024
 *      Author: Phatt
 */
#include "globalVar.h"

void sendall(){
	registerFrame[0x04].U16 = gripperMovementActualStatus;
	registerFrame[0x10].U16 = zMovementStatus;
	registerFrame[0x11].U16 = zPosition * 10;
	registerFrame[0x12].U16 = zSpeed;
	registerFrame[0x13].U16 = zAccel;
	registerFrame[0x40].U16 = xPosition;
}
