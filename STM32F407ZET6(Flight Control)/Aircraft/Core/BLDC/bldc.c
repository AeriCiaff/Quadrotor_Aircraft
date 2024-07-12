#include "main.h"
#include "tim.h"
#include "pid.h"


void Motor_Init()
{
	__HAL_TIM_SetCompare(&htim11, TIM_CHANNEL_1, 2000);
	__HAL_TIM_SetCompare(&htim12, TIM_CHANNEL_1, 2000);
	__HAL_TIM_SetCompare(&htim13, TIM_CHANNEL_1, 2000);
	__HAL_TIM_SetCompare(&htim14, TIM_CHANNEL_1, 2000);
	HAL_Delay(2000);
	__HAL_TIM_SetCompare(&htim11, TIM_CHANNEL_1, 1000);
	__HAL_TIM_SetCompare(&htim12, TIM_CHANNEL_1, 1000);
	__HAL_TIM_SetCompare(&htim13, TIM_CHANNEL_1, 1000);
	__HAL_TIM_SetCompare(&htim14, TIM_CHANNEL_1, 1000);
	HAL_Delay(2000);
}

void Motor_Speed(TIM_HandleTypeDef *htim, uint32_t Channel, uint16_t Speed)
{
	__HAL_TIM_SetCompare(htim, Channel, Speed);
}

void Motor_Land()
{
	Motor_Speed(&htim11, TIM_CHANNEL_1, 1100);
	Motor_Speed(&htim12, TIM_CHANNEL_1, 1100);
	Motor_Speed(&htim13, TIM_CHANNEL_1, 1100);
	Motor_Speed(&htim14, TIM_CHANNEL_1, 1100);
}

void Motor_Hanging(uint16_t Speed)
{
	Motor_Speed(&htim11, TIM_CHANNEL_1, Speed);
	Motor_Speed(&htim12, TIM_CHANNEL_1, Speed);
	Motor_Speed(&htim13, TIM_CHANNEL_1, Speed);
	Motor_Speed(&htim14, TIM_CHANNEL_1, Speed);
}

void Motor_Forward(uint16_t Speed)
{
	if(Speed > 1000 && Speed < 2000)
	{
		Motor_Speed(&htim11, TIM_CHANNEL_1, Speed + 10);
		Motor_Speed(&htim12, TIM_CHANNEL_1, Speed);
		Motor_Speed(&htim13, TIM_CHANNEL_1, Speed);
		Motor_Speed(&htim14, TIM_CHANNEL_1, Speed + 10);
	}
}

void Motor_Back(uint16_t Speed)
{
	if(Speed > 1000 && Speed < 2000)
	{
		Motor_Speed(&htim11, TIM_CHANNEL_1, Speed);
		Motor_Speed(&htim12, TIM_CHANNEL_1, Speed + 10);
		Motor_Speed(&htim13, TIM_CHANNEL_1, Speed + 10);
		Motor_Speed(&htim14, TIM_CHANNEL_1, Speed);
	}
}

void Motor_Right_Y(uint16_t Speed)
{
	if(Speed > 1000 && Speed < 2000)
	{
		Motor_Speed(&htim11, TIM_CHANNEL_1, Speed + 10);
		Motor_Speed(&htim12, TIM_CHANNEL_1, Speed + 10);
		Motor_Speed(&htim13, TIM_CHANNEL_1, Speed);
		Motor_Speed(&htim14, TIM_CHANNEL_1, Speed);
	}
}

void Motor_Left_Y(uint16_t Speed)
{
	if(Speed > 1000 && Speed < 2000)
	{
		Motor_Speed(&htim11, TIM_CHANNEL_1, Speed);
		Motor_Speed(&htim12, TIM_CHANNEL_1, Speed);
		Motor_Speed(&htim13, TIM_CHANNEL_1, Speed + 10);
		Motor_Speed(&htim14, TIM_CHANNEL_1, Speed + 10);
	}
}

void Motor_Right_Z(uint16_t Speed)
{
	if(Speed > 1000 && Speed < 2000)
	{
		Motor_Speed(&htim11, TIM_CHANNEL_1, Speed);
		Motor_Speed(&htim12, TIM_CHANNEL_1, Speed + 10);
		Motor_Speed(&htim13, TIM_CHANNEL_1, Speed);
		Motor_Speed(&htim14, TIM_CHANNEL_1, Speed + 10);
	}
}

void Motor_Left_Z(uint16_t Speed)
{
	if(Speed > 1000 && Speed < 2000)
	{
		Motor_Speed(&htim11, TIM_CHANNEL_1, Speed + 10);
		Motor_Speed(&htim12, TIM_CHANNEL_1, Speed);
		Motor_Speed(&htim13, TIM_CHANNEL_1, Speed + 10);
		Motor_Speed(&htim14, TIM_CHANNEL_1, Speed);
	}
}

uint16_t Motor_Rise(uint16_t Speed)
{
	if(Speed < 2000)
	{
		Speed = Speed + 5;
		Motor_Speed(&htim11, TIM_CHANNEL_1, Speed);
		Motor_Speed(&htim12, TIM_CHANNEL_1, Speed);
		Motor_Speed(&htim13, TIM_CHANNEL_1, Speed);
		Motor_Speed(&htim14, TIM_CHANNEL_1, Speed);
	}

	return Speed;
}

uint16_t Motor_Down(uint16_t Speed)
{
	if(Speed >1000)
	{
		Speed = Speed - 5;
		Motor_Speed(&htim11, TIM_CHANNEL_1, Speed);
		Motor_Speed(&htim12, TIM_CHANNEL_1, Speed);
		Motor_Speed(&htim13, TIM_CHANNEL_1, Speed);
		Motor_Speed(&htim14, TIM_CHANNEL_1, Speed);
	}
	
	return Speed;
}

uint16_t Motor_Stop(uint16_t Speed)
{
	Motor_Speed(&htim11, TIM_CHANNEL_1, 1000);
	Motor_Speed(&htim12, TIM_CHANNEL_1, 1000);
	Motor_Speed(&htim13, TIM_CHANNEL_1, 1000);
	Motor_Speed(&htim14, TIM_CHANNEL_1, 1000);
	Speed = 1100;
	
	return Speed;
}

uint16_t Motor_High_Position(PID *pid,uint16_t Speed)
{
	pid->Kd = 0;
	pid->Ki = 0;
	pid->Kd = 0;
	pid->error = 0;
	PID_Position_Calculate(pid);
	
	Speed = Speed + pid->output;
	Motor_Speed(&htim11, TIM_CHANNEL_1, Speed);
	Motor_Speed(&htim12, TIM_CHANNEL_1, Speed);
	Motor_Speed(&htim13, TIM_CHANNEL_1, Speed);
	Motor_Speed(&htim14, TIM_CHANNEL_1, Speed);
	
	return Speed;
}

void Motor_XY_Position(PID *pid, uint16_t Speed)
{
	PID_Reset(pid);
	
	
}