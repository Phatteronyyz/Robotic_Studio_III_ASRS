/*
 * gripper.c
 *
 *  Created on: May 21, 2024
 *      Author: Phatt
 */
#include <stdio.h>
#include <math.h>
#include "globalVar.h"

void readLead(){
	leadMin = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7);
	leadMax = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6);
	if(leadMin == 1 && leadMax == 0){
		movementActualStatus = 1;
	}
	else if(leadMin == 0 && leadMax == 1){
		movementActualStatus = 2;
	}
	else{
		movementActualStatus = 0;
	}

	if(registerFrame[0x02].U16 == 1){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 0);
	}
	else if(registerFrame[0x02].U16 == 0){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 1);
	}

	if(registerFrame[0x03].U16 == 1){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 0);
	}
	else if(registerFrame[0x03].U16 == 0){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 1);
	}
}
