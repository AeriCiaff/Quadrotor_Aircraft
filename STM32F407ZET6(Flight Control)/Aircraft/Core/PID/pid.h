#ifndef __PID_H
#define __PID_H

typedef struct PID{
	float Kp;
	float Ki;
	float Kd;
	float error;
	float error_pre;
	float error_pre_pre;
	float error_sum;
	float target;
	float input;
	float output;
}PID;

void PID_Init(PID* pid);
void PID_Reset(PID* pid);
void PID_Position_Calculate(PID* pid);
void PID_Increase_Calculate(PID* pid);

#endif