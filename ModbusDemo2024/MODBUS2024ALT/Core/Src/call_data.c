/*
 * call_data.c
 *
 *  Created on: Apr 29, 2024
 *      Author: Phatt
 */
#include "globalVar.h"
#include "math.h"

void sendall(){
	// Base_System_status
//	registerFrame[0x01].U16 = baseSystemStatus;
	// Vacuum Status
//	registerFrame[0x02].U16 = 0;
	// Movement Status
//	registerFrame[0x03].U16 = 0;
	// Movement Actual Status
	registerFrame[0x04].U16 = movementActualStatus;
	// z-axis Moving Status
	registerFrame[0x10].U16 = zMovingStatus;
	// z-axis Actual Position
	registerFrame[0x11].U16 = (floor((linearPos * 1000000))/100000) + 800;
	// z-axis Actual Speed
	registerFrame[0x12].U16 = (floor((zActualSpeed * 1000000))/100000);
	// z-axis Actual Acceleration
	registerFrame[0x13].U16 = (floor((zAccel * 1000000))/100000);
	// Pick order
//	registerFrame[0x21].U16 = 0;
	// Place order
//	registerFrame[0x22].U16 = 0;
	// 1st shelves position
//	registerFrame[0x23].U16 = firstShelvesPosition;
	// 2nd shelves position
//	registerFrame[0x24].U16 = 0;
	// 3rd shelves position
//	registerFrame[0x25].U16 = 0;
	// 4th shelves position
//	registerFrame[0x26].U16 = 0;
	// 5th shelves position
//	registerFrame[0x27].U16 = 0;
	// Goal point z
//	registerFrame[0x30].U16 = 0;
	//x-axis Actual position
	registerFrame[0x40].U16 = (xAxisPosition * 10);
}
