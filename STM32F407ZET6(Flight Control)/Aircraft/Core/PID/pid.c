#include <stdio.h>

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

void PID_Init(PID* pid) {
	pid->Kp = 0;
	pid->Ki = 0;
	pid->Kd = 0;
	pid->error = 0;
	pid->error_pre = 0;
	pid->error_pre_pre = 0;
	pid->error_sum = 0;
	pid->target = 0;
	pid->input = 0;
	pid->output = 0;
}

void PID_Reset(PID* pid) {
	pid->error = 0;
	pid->error_pre = 0;
	pid->error_pre_pre = 0;
	pid->error_sum = 0;
	pid->target = 0;
	pid->input = 0;
	pid->output = 0;
}

void PID_Increase_Calculate(PID* pid) {
	pid->error = pid->target - pid->input;

	float P = pid->Kp * (pid->error - pid->error_pre);
	float I = pid->Ki * pid->error;
	float D = pid->Kd * (pid->error - 2 * pid->error_pre + pid->error_pre_pre);

	pid->error_pre_pre = pid->error_pre;
	pid->error_pre = pid->error;

	pid->output = P + I + D;
}

void PID_Position_Calculate(PID* pid) {
	pid->error = pid->target - pid->input;
	pid->error_sum = pid->error_sum + pid->error;

	float P = pid->Kp * pid->error;
	float I = pid->Ki * pid->error_sum;
	float D = pid->Kd * (pid->error - pid->error_pre);

	pid->error_pre = pid->error;

	pid->output = P + I + D;
}