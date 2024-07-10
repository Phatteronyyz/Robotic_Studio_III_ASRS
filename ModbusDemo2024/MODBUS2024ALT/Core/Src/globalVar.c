#include "main.h"
#include "ModBusRTU.h"

enum{
	start, goPick, goPlace, Grap, Place
};

u16u8_t registerFrame[200];

uint8_t modeSelection = 0;

uint8_t baseSystemStatus, vacuumStatus, movementStatus, movementActualStatus;
uint32_t zMovingStatus, zActualPosition, zActualSpeed, zAccel;
uint16_t pickOrder[5] = {0}, placeOrder[5] = {0}, currentOrder = 0;
float posOrder[5];
uint32_t firstShelvesPosition, secondShelvesPosition, thirdShelvesPosition, fourthShelvesPosition, fifthShelvesPosition;
uint32_t goalPointZ;
int32_t xAxisPosition = 0;

uint32_t QEIReadRaw = 0, QEIOfRound = 0, useQEIReadRaw = 0;
double degreePerRound = 0.0;
float linearPos = 0.0;
int motoring = 0, remoteCheck = 0;

double setposition = 0.0, err = 0.0, errr = 0.0;
double absVfb = 0.0;
uint64_t usePWM = 0, fPWM = 0, thispwm = 0;
int8_t motorDirection = 0, isMotorCanMoveUp = 0, isMotorCanMoveDown = 0, home_trig = 0, home_select = 0, jogMode_subState = 0;
uint64_t tickk = 0, home_timeStamp = 0, home_trigger = 0, pointMode_trig = 0, pointMode_timeStamp = 0, pointMode_timeTrig = 0 , run_jog_trig  = 0, run_jog_timestamp = 0, run_jog_stage = 0;
uint64_t goPoint_trig = 0 , jogModeGoal = 0, gopoint_act = 0, goPointgoal = 0, goPoint_times = 0, jog_goPoint_actt = 0, point_traj_trig = 0, jogMode_trig = 0, jogModeState = start, jogMode_timeStamp = 0;

//int32_t ServoTime, dt, ServoPeriod;
//uint16_t Rise, Fall;

// remote
uint64_t ch1_timestamp = 0, JoyxPosition_timestamp = 0, home_delay = 0;
int32_t zUp, zUp_dt, zDown, zDown_dt;
uint16_t zUp_Rise, zUp_Fall, zDown_Rise, zDown_Fall;
int32_t joySel1, joySel2, joySel1_dt, joySel2_dt;
uint16_t joySel1_Rise, joySel1_Fall, joySel2_Rise, joySel2_Fall;
int32_t joySave, joySave_dt;
uint16_t joySave_Rise, joySave_Fall;
uint8_t ShelvesSelect = 0;
int32_t JoyxPosition, JoyxPosition_dt;
uint16_t JoyxPosition_Rise, JoyxPosition_Fall;
//int32_t ch3_stepUp, ch3_dt;
//uint16_t ch3_Rise, ch3_Fall;
//int32_t ch4_stepDown, ch4_dt;
//uint16_t ch4_Rise, ch4_Fall;
//int32_t ch5_saveShelves, ch5_dt;
//uint16_t ch5_Rise, ch5_Fall;
//int32_t ch6_selectShelves1, ch6_dt;
//uint16_t ch6_Rise, ch6_Fall;
//int32_t ch7_selectShelves2, ch7_dt;
//uint16_t ch7_Rise, ch7_Fall;
// limit sensor
uint16_t limitMin = 0, limitMax = 0;

//gripper
uint8_t leadMin = 0, leadMax = 0, Emer = 0;

float trajec_target;

uint64_t modBusTimeStamp = 0, p1_timeStamp = 10, p2_timeStamp = 10, p1_trig = 0, p2_trig = 0;

uint8_t finish_state = 0;
