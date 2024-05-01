/*
 * motor_control.c
 *
 *  Created on: Apr 29, 2024
 *      Author: Phatt
 */
#include "globalVar.h"
#include "math.h"

void motot_cal(){
	QEIOfRound = QEIReadRaw % 8192;
	degreePerRound = (QEIOfRound * 360.0) / 8192.0;
	linearPos = ((24.95 * M_PI) / 8192.0) * QEIReadRaw;
	err = setposition - linearPos;
}

