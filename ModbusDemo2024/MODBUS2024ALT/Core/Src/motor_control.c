/*
 * motor_control.c
 *
 *  Created on: Apr 29, 2024
 *      Author: Phatt
 */
#include "globalVar.h"
#include "math.h"


//void init_motor_cal(){
//	motor_basic_cal();
//}
//
//void motor_moveup(){
//	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15,GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,GPIO_PIN_SET);
//}
//
//void motor_movedown(){
//	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15,GPIO_PIN_SET);
//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7,GPIO_PIN_RESET);
//}
//
//void motor_basic_cal(){
//	//QEI per round
//	QEIOfRound = QEIReadRaw % 8192;
//	//degree per round
//	degreePerRound = (QEIOfRound * 360.0) / 8192.0;
//	//position on z-zxis
//	linearPos = ((25.01093 * M_PI) / 8192.0) * QEIReadRaw; //24.95
//}
//
void is_motor_should_run(){
	limitMin = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1);
	limitMax = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14);
	// motor can move up and down
	if(!limitMax && !limitMin){
		isMotorCanMoveUp = 1;
		isMotorCanMoveDown = 1;
	}
	// motor can only move up
	else if(limitMin){
		isMotorCanMoveUp = 1;
		isMotorCanMoveDown = 0;
	}
	//motor can only move down
	else if(limitMax){
		isMotorCanMoveUp = 0;
		isMotorCanMoveDown = 1;
	}
}
//
//void PWM_control(){
//	//distance between goal and actual_z-position
//	err = setposition - linearPos;
//
//	absVfb = fabs(Vfeedback);
//	fPWM = (absVfb / 10);
//
//	if(fPWM < 500 && fPWM > 240) usePWM = 1450;
//	else if(fPWM > 2000) usePWM = 2000;
//	else usePWM = fPWM;
//	if(err < -580) usePWM = 0 ;
//	if(linearPos >= 580) usePWM = 0;
//		errr = setposition - linearPos;
////	if(errr > 300) errr -= 600;
////	else if(errr < -300) errr += 600;
//	if(errr < 0){
//		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0,GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1,GPIO_PIN_RESET);
//	}
//	else if(errr > 0){
//		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0,GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1,GPIO_PIN_SET);
//	}
//}
//
//void x_axis_control_by_remote(){
//	ch2_timestamp = HAL_GetTick();
//	if(ch2_timestamp < HAL_GetTick()){
//		if(ch2_xPosition < 1410 && ch2_xPosition > 920 && xAxisPosition > -100){
//			xAxisPosition -= 1;
//		}
//		else if(ch2_xPosition > 1450 && ch2_xPosition < 1960 && xAxisPosition < 100){
//			xAxisPosition += 1;
//		}
//		ch2_timestamp = HAL_GetTick() + 100;
//	}
//}
//


void readLimit(){
 	limitMin = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1);
	limitMax = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14);
}

//void motorQueue(){
//	if(modeSelection == 0){
//		z_axis_control_by_remote();
//	}
//}


