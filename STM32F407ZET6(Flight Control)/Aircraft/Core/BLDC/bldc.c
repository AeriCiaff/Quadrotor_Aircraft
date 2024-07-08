#include "main.h"
#include "tim.h"


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
	Motor_Speed(&htim11, TIM_CHANNEL_1, 1040);
	Motor_Speed(&htim12, TIM_CHANNEL_1, 1040);
	Motor_Speed(&htim13, TIM_CHANNEL_1, 1040);
	Motor_Speed(&htim14, TIM_CHANNEL_1, 1040);
}