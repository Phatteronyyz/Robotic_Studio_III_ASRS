#include <stdio.h>
#include <math.h>
#include "globalVar.h"

void watch_mode(){
	if(registerFrame[0x01].U16 == 1){

	}
	else if(registerFrame[0x01].U16 == 2){
		do_home();
	}
	else if(registerFrame[0x01].U16 == 4){

	}
	else if(registerFrame[0x01].U16 == 8){
		run_point_mode();
	}
}

void do_home(){
	//set base status to 0 (default)
	registerFrame[0x01].U16 = 0;
	//set moving status to home
	registerFrame[0x10].U16 = 2;
	//Homing
	if(registerFrame[0x11].U16 == 0){
		//when finished turn moving status to 0
		registerFrame[0x10].U16 = 0;
	}
}

//void set_shelves(){
//	//set base status to 0 (default)
//	registerFrame[0x01].U16 = 0;
//	registerFrame[0x10].U16 = 1;
////	if(button pressed) save shelves poosition;
//	registerFrame[0x10].U16 = 0;
//}
//
void run_point_mode(){
	registerFrame[0x01].U16 = 0;
	registerFrame[0x10].U16 = 16;
	HAL_Delay(500);
	zPosition = 300;
//	going to point
	registerFrame[0x10].U16 = 0;
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
