/*
 * globalVar.h
 *
 *  Created on: Apr 29, 2024
 *      Author: Phatt
 */
#include "ModBusRTU.h"

#ifndef INC_GLOBALVAR_H_
#define INC_GLOBALVAR_H_

extern u16u8_t registerFrame[200];
extern uint8_t gripperMovementStatus, gripperMovementActualStatus;
extern uint8_t zMovementStatus;
extern double zPosition, zSpeed, zAccel, zPoint, xPosition;
extern char pickOrder[6], placeOrder[6];
extern double firstShelve, secondShelve, thirdShelve, fourthShelve, fifthShelve;

#endif /* INC_GLOBALVAR_H_ */
