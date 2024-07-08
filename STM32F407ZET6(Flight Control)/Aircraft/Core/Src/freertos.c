/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bldc.h"
#include "stdio.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "bmp280.h"
#include "oled.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
char Temp[] = "Temp:";
char Press[] = "Press:";
char High[] = "High:";
char Yaw[] = "Yaw:";
char Pitch[] = "Pitch:";
char Roll[] = "Roll:";
uint16_t Speed;
/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId myTask02Handle;
osThreadId myTask03Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
struct Angle{
	float pitch;
	float roll;
	float yaw;
}Angle;

struct BMP280Sensor{
	float temp;
	float press;
	float high;
}BMP280Sensor;
/* USER CODE END FunctionPrototypes */

void MPU6050_Task(void const * argument);
void BMP280_Task(void const * argument);
void Hanging(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, MPU6050_Task, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of myTask02 */
  osThreadDef(myTask02, BMP280_Task, osPriorityNormal, 0, 128);
  myTask02Handle = osThreadCreate(osThread(myTask02), NULL);

  /* definition and creation of myTask03 */
  osThreadDef(myTask03, Hanging, osPriorityNormal, 0, 128);
  myTask03Handle = osThreadCreate(osThread(myTask03), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_MPU6050_Task */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_MPU6050_Task */
void MPU6050_Task(void const * argument)
{
  /* USER CODE BEGIN MPU6050_Task */
	int ret = 0;
	do{
		ret = MPU6050_DMP_Init();
		osDelay(1000);
	}while(ret);
  /* Infinite loop */
  for(;;)
  {
		MPU6050_DMP_GetData(&Angle.pitch,&Angle.roll,&Angle.yaw);
		osDelay(200);
  }
  /* USER CODE END MPU6050_Task */
}

/* USER CODE BEGIN Header_BMP280_Task */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_BMP280_Task */
void BMP280_Task(void const * argument)
{
  /* USER CODE BEGIN BMP280_Task */
  /* Infinite loop */
  for(;;)
  {
		BMP280_Measure_Cmd();
		BMP280_ReadData();
		BMP280Sensor.temp = BMP280_Calculate_Temp();
		BMP280Sensor.press = BMP280_Calculate_Press();
		BMP280Sensor.high = BMP280_HighCalculate();
    osDelay(200);
  }
  /* USER CODE END BMP280_Task */
}

/* USER CODE BEGIN Header_Hanging */
/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Hanging */
void Hanging(void const * argument)
{
  /* USER CODE BEGIN Hanging */
  /* Infinite loop */
  for(;;)
  {
		Motor_Speed(&htim11, TIM_CHANNEL_1, Speed);
		Motor_Speed(&htim12, TIM_CHANNEL_1, Speed);
		Motor_Speed(&htim13, TIM_CHANNEL_1, Speed);
		Motor_Speed(&htim14, TIM_CHANNEL_1, Speed);
    osDelay(1);
  }
  /* USER CODE END Hanging */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
