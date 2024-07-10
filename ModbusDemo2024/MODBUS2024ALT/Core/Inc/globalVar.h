/*
 * globalVar.h
 *
 *  Created on: Apr 29, 2024
 *      Author: Phatt
 */
#include "ModBusRTU.h"

#ifndef INC_GLOBALVAR_H_
#define INC_GLOBALVAR_H_

extern enum{
	goPick, goPlace, Grap, Place
};

extern uint8_t modeSelection;

extern u16u8_t registerFrame[200];
extern uint8_t baseSystemStatus, vacuumStatus, movementStatus, movementActualStatus;
extern uint32_t zMovingStatus, zActualPosition, zActualSpeed, zAccel;
extern uint16_t pickOrder[5], placeOrder[5], currentOrder;
extern float posOrder[5];
extern uint32_t firstShelvesPosition, secondShelvesPosition, thirdShelvesPosition, fourthShelvesPosition, fifthShelvesPosition;
extern uint32_t goalPointZ;
extern int32_t xAxisPosition;

extern uint32_t QEIReadRaw, QEIOfRound, useQEIReadRaw;
extern double degreePerRound;
extern float linearPos;
extern int motoring, remoteCheck;

extern double setposition, err, errr;
extern double absVfb;
extern uint64_t usePWM, fPWM, thispwm;
extern int8_t motorDirection, isMotorCanMoveUp, isMotorCanMoveDown, home_trig, home_select, jogMode_subState;
extern uint64_t tickk, home_timeStamp, home_trigger, pointMode_trig, pointMode_timeStamp, pointMode_timeTrig, run_jog_trig, run_jog_timestamp, run_jog_stage;
extern uint64_t goPoint_trig, jogModeGoal, gopoint_act, goPointgoal, goPoint_times, jog_goPoint_actt, point_traj_trig, jogMode_trig, jogModeState, jogMode_timeStamp;

// remote
extern uint64_t ch1_timestamp, JoyxPosition_timestamp, home_delay;
extern int32_t zUp, zUp_dt, zDown, zDown_dt;
extern uint16_t zUp_Rise, zUp_Fall, zDown_Rise, zDown_Fall;
extern int32_t joySel1, joySel2, joySel1_dt, joySel2_dt;
extern uint16_t joySel1_Rise, joySel1_Fall, joySel2_Rise, joySel2_Fall;
extern int32_t joySave, joySave_dt;
extern uint16_t joySave_Rise, joySave_Fall;
extern uint8_t ShelvesSelect;
extern int32_t JoyxPosition, JoyxPosition_dt;
extern  uint16_t JoyxPosition_Rise, JoyxPosition_Fall;
//extern int32_t ch3_stepUp, ch3_dt;
//extern uint16_t ch3_Rise, ch3_Fall;
//extern int32_t ch4_stepDown, ch4_dt;
//extern uint16_t ch4_Rise, ch4_Fall;
//extern int32_t ch5_saveShelves, ch5_dt;
//extern uint16_t ch5_Rise, ch5_Fall;
//extern int32_t ch6_selectShelves1, ch6_dt;
//extern uint16_t ch6_Rise, ch6_Fall;
//extern int32_t ch7_selectShelves2, ch7_dt;
//extern uint16_t ch7_Rise, ch7_Fall;

// limit sensor
extern uint16_t limitMin, limitMax, Emer;

//gripper
extern uint8_t leadMin, leadMax, pushpull, vacc;

extern float trajec_target;

extern uint64_t modBusTimeStamp, p1_timeStamp, p2_timeStamp, p1_trig, p2_trig;

extern uint8_t finish_state;


#endif /* INC_GLOBALVAR_H_ */
