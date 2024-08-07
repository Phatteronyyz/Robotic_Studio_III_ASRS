/*
 * motor_control.h
 *
 *  Created on: Apr 29, 2024
 *      Author: Phatt
 */

#ifndef INC_MOTOR_CONTROL_H_
#define INC_MOTOR_CONTROL_H_

void init_motor_cal();
void motor_moveup();
void motor_movedown();
void motor_basic_cal();
void is_motor_should_run();
void PWM_control();
void x_axis_control_by_remote();
void motorQueue();


#endif /* INC_MOTOR_CONTROL_H_ */
