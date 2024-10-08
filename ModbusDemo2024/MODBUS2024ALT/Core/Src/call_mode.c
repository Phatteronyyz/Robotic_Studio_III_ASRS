#include <stdio.h>
#include <math.h>
#include "globalVar.h"

//void call_all_mode(){
//	do_home();
//}
//

void watch_mode(){
	if(registerFrame[0x01].U16 == 1){
		modeSelection = 4;
	}
	else if(registerFrame[0x01].U16 == 2){
		modeSelection = 1;
		if(!limitMin) home_select = 1;
		else if(limitMin) home_select = 2;
	}
	else if(registerFrame[0x01].U16 == 4){
		currentOrder = 0;
		jogModeState = goPick;
		modeSelection = 3;
		jogMode_timeStamp = tickk + 2000;
	}
	else if(registerFrame[0x01].U16 == 8){
		modeSelection = 2;
		pointMode_timeStamp = tickk + 2000;
	}

	if(modeSelection == 1){
		do_home();
		p1Blink();
		p2Blink();
	}
	else if(modeSelection == 2){
		run_point_mode();
	}
	else if(modeSelection == 3){
		run_jog_mode();
		p1On();
		p2On();
	}
	else if(modeSelection == 4){
		set_shelves();
	}
}

void do_home(){
	registerFrame[0x01].U16 = 0;
	registerFrame[0x10].U16 = 2;

	if(!limitMin){
		motor_run(7000, 2);
	}

	else if(limitMin){
		home_timeStamp = HAL_GetTick() + 1000;
		motor_run(0, 3);
		home_trigger = 1;
		modeSelection = 0;
	}
}

void set_shelves(){
	//set base status to 0 (default)
	registerFrame[0x01].U16 = 0;
	registerFrame[0x10].U16 = 1;
	if(joySave > 39000){
		if(ShelvesSelect == 1){
//			firstShelvesPosition = floor((linearPos * 1000000))/100000;
			registerFrame[0x23].U16 = floor((linearPos * 1000000))/100000;
			firstShelvesPosition = registerFrame[0x23].U16;
		}
		else if(ShelvesSelect == 2){
//			secondShelvesPosition = floor((linearPos * 1000000))/100000;
			registerFrame[0x24].U16 = floor((linearPos * 1000000))/100000;
			secondShelvesPosition = registerFrame[0x24].U16;
		}
		else if(ShelvesSelect == 3){
//			thirdsecondShelvesPosition = floor((linearPos * 1000000))/100000;
			registerFrame[0x25].U16 = floor((linearPos * 1000000))/100000;
			thirdShelvesPosition = registerFrame[0x25].U16;
		}
		else if(ShelvesSelect == 4){
//			fourthsecondShelvesPosition = floor((linearPos * 1000000))/100000;
			registerFrame[0x26].U16 = floor((linearPos * 1000000))/100000;
			fourthShelvesPosition = registerFrame[0x26].U16;
		}
		else if(ShelvesSelect == 5){
//			fifthsecondShelvesPosition = floor((linearPos * 1000000))/100000;
			registerFrame[0x27].U16 = floor((linearPos * 1000000))/100000;
			fifthShelvesPosition = registerFrame[0x27].U16;
		}
	}
	if(ShelvesSelect == 6 && fifthShelvesPosition != 0){
		registerFrame[0x10].U16 = 0;
		modeSelection = 0;
	}
}
//
void run_point_mode(){
	remoteCheck = 5;
	registerFrame[0x01].U16 = 0;
	registerFrame[0x10].U16 = 16;
	if(point_traj_trig == 0){
		trajec_target = (registerFrame[0x30].U16 / 10) - 80;
		point_traj_trig = 1;
	}
	else if(finish_state == 1 && point_traj_trig == 1 && pointMode_timeStamp < tickk){
		registerFrame[0x10].U16 = 0;
		point_traj_trig = 0;
		modeSelection = 0 ;
	}
}

void run_jog_mode(){
	registerFrame[0x01].U16 = 0;
	uint16_t pickall = registerFrame[0x21].U16, placeall = registerFrame[0x22].U16;
	posOrder[0] = firstShelvesPosition/10;
	posOrder[1] = secondShelvesPosition/10;
	posOrder[2] = thirdShelvesPosition/10;
	posOrder[3] = fourthShelvesPosition/10;
	posOrder[4] = fifthShelvesPosition/10;
	pickOrder[0] = pickall/10000;
	pickOrder[1] = (pickall/1000)%10;
	pickOrder[2] = (pickall/100)%10;
	pickOrder[3] = (pickall/10)%10;
	pickOrder[4] = pickall%10;
	placeOrder[0] = placeall/10000;
	placeOrder[1] = (placeall/1000)%10;
	placeOrder[2] = (placeall/100)%10;
	placeOrder[3] = (placeall/10)%10;
	placeOrder[4] = placeall%10;

	if(jogModeState == goPick){
		registerFrame[0x10].U16 = 4;
		if(jogMode_trig == 0){
			trajec_target = posOrder[pickOrder[currentOrder] - 1] - 3;
			jogMode_trig = 1;
		}
		if(finish_state == 1 && jogMode_timeStamp < tickk){
			jogModeState = Grap;
			jogMode_timeStamp = tickk + 1500;
			jogMode_trig = 0;
		}
	}
	else if(jogModeState == Grap){
//		if(jogMode_subState == 0 && jogMode_timeStamp < tickk){
//			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 0);
//			jogMode_subState = 1;
//		}
//		else if(jogMode_subState == 1 && !leadMax){
//			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 0);
//			jogMode_timeStamp = tickk + 200;
//			jogMode_subState = 2;
//		}
//		else if(jogMode_subState == 2 && jogMode_timeStamp < tickk){
//			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 1);
//			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 0);
//			jogMode_subState = 3;
//			jogMode_timeStamp = tickk + 200;
//		}
//		else if(jogMode_subState == 3 && !leadMin){
//			jogMode_subState = 4;
//			jogMode_timeStamp = tickk + 200;
//		}

		if(jogMode_timeStamp - 1000 < tickk){
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 0);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 0);
		}
		if(jogMode_timeStamp - 350 < tickk){
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 1);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 0);
		}
		if(jogMode_timeStamp < tickk){
			jogModeState = goPlace;
			jogMode_trig = 0;
			jogMode_timeStamp = tickk + 2500;
		}
	}
	else if(jogModeState == goPlace){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 0);
		registerFrame[0x10].U16 = 8;
		if(jogMode_trig == 0){
			trajec_target = posOrder[placeOrder[currentOrder] - 1] + 10;
			jogMode_trig = 1;
		}
		if(finish_state == 1 && jogMode_timeStamp < tickk){
			jogModeState = Place;
			jogMode_timeStamp = tickk + 1500;
			jogMode_trig = 0;
//			currentOrder += 1;
		}
	}
	else if(jogModeState == Place){
		if(jogMode_timeStamp -1200 < tickk){
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 0);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 0);
		}
		else if(jogMode_timeStamp - 900 < tickk){
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 1);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 0);
		}
		else if(jogMode_timeStamp - 700 < tickk){
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 1);
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 1);
		}
		else if(jogMode_timeStamp - 500 < tickk){
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, 0);
		}
		else if(jogMode_timeStamp > tickk){
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, 0);
		}
		if(jogMode_timeStamp < tickk){
			jogModeState = goPick;
			jogMode_trig = 0;
			jogMode_timeStamp = tickk + 2500;
			currentOrder += 1;
		}
	}

	if(currentOrder == 5){
		registerFrame[0x10].U16 = 0;
		modeSelection = 0;
		currentOrder = 0;
	}

}

void p2On(){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
}

void p1On(){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 0);
}

void p2Off(){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);
}

void p1Off(){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, 1);
}

void p2Blink(){
	if(p2_timeStamp <= tickk){
		p2_trig = (p2_trig + 1) %2;
		if(p2_trig) p2On();
		else if(!p2_trig) p2Off();
		p2_timeStamp = tickk + 500;
	}
}

void p1Blink(){
	if(p1_timeStamp <= tickk){
		p1_trig = (p1_trig + 1) %2;
		if(p1_trig) p1On();
		else if(!p1_trig) p1Off();
		p1_timeStamp = tickk + 500;
	}
}
//
//
//void run_jog_mode(){
//	registerFrame[0x01] = 0;
//	uint16_t pickall = registerFrame[0x21], placeall = registerFrame[0x22];
//	pickOrder[0] = pickall/10000;
//	pickOrder[1] = (pickall/1000)%10;
//	pickOrder[2] = (pickall/100)%10;
//	pickOrder[3] = (pickall/10)%10;
//	pickOrder[4] = pickall%10;
//	placeOrder[0] = placeall/10000;
//	placeOrder[1] = (placeall/1000)%10;
//	placeOrder[2] = (placeall/100)%10;
//	placeOrder[3] = (placeall/10)%10;
//	placeOrder[4] = placeall%10;
//	double allshelves[5] = {fifthShelve,secondShelve,thirdShelve,fourthShelve,fifthShelve};
////	for(int i=0;t<5;i++){
////		registerFrame[0x10] = 4;
////		run thru each point
////		registerFrame[0x10] = 8;
////	}
//	registerFrame[0x10] = 0;
//}

//void z_axis_control_by_remote(){
//	if(zUp < -2000 && zUp > -3000 && zDown > -2000){
//		remoteCheck = 1;
//		motor_run(10000, 1);
//	}
//	else if(zDown < -1900 && zDown > -3000 && zUp > -2000){
//		remoteCheck = 2;
//		motor_run(10000, 2);
//	}
//	else{
//		motor_run(0, 3);
//		remoteCheck = 0;
//	}
//}
