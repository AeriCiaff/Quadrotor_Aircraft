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
/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId myTask02Handle;
osThreadId myTask03Handle;
osThreadId myTask04Handle;
osThreadId myTask05Handle;

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
void MPU6050_ShowTask(void const * argument);
void BMP280_ShowTask(void const * argument);
void OLED_ShowTask(void const * argument);

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
  osThreadDef(myTask03, MPU6050_ShowTask, osPriorityNormal, 0, 128);
  myTask03Handle = osThreadCreate(osThread(myTask03), NULL);

  /* definition and creation of myTask04 */
  osThreadDef(myTask04, BMP280_ShowTask, osPriorityNormal, 0, 128);
  myTask04Handle = osThreadCreate(osThread(myTask04), NULL);

  /* definition and creation of myTask05 */
  osThreadDef(myTask05, OLED_ShowTask, osPriorityNormal, 0, 128);
  myTask05Handle = osThreadCreate(osThread(myTask05), NULL);

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

/* USER CODE BEGIN Header_MPU6050_ShowTask */
/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_MPU6050_ShowTask */
void MPU6050_ShowTask(void const * argument)
{
  /* USER CODE BEGIN MPU6050_ShowTask */

  /* Infinite loop */
  for(;;)
  {
		OLED_ShowString(1,1,Yaw,16);
		OLED_ShowNum(33,1,Angle.yaw,6,16);
    OLED_ShowString(1,3,Pitch,16);
    OLED_ShowNum(49,3,Angle.pitch,6,16);
    OLED_ShowString(1,5,Roll,16);
    OLED_ShowNum(41,5,Angle.roll,6,16);
		osDelay(50);
  }
  /* USER CODE END MPU6050_ShowTask */
}

/* USER CODE BEGIN Header_BMP280_ShowTask */
/**
* @brief Function implementing the myTask04 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_BMP280_ShowTask */
void BMP280_ShowTask(void const * argument)
{
  /* USER CODE BEGIN BMP280_ShowTask */

  /* Infinite loop */
  for(;;)
  {
		OLED_ShowString(1,1,Temp,16);
		OLED_ShowNum(41,1,BMP280Sensor.temp,6,16);
		OLED_ShowString(1,3,Press,16);
		OLED_ShowNum(49,3,BMP280Sensor.press,9,16);
		OLED_ShowString(1,5,High,16);
		OLED_ShowNum(41,5,BMP280Sensor.high,7,16);
		osDelay(50);
  }
  /* USER CODE END BMP280_ShowTask */
}

/* USER CODE BEGIN Header_OLED_ShowTask */
/**
* @brief Function implementing the myTask05 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_OLED_ShowTask */
void OLED_ShowTask(void const * argument)
{
  /* USER CODE BEGIN OLED_ShowTask */
	vTaskSuspend(myTask04Handle);
	vTaskSuspend(myTask03Handle);
  /* Infinite loop */
  for(;;)
  {
		vTaskSuspend(myTask04Handle);
		OLED_Clear();
		vTaskResume(myTask03Handle);
		osDelay(3000);
		vTaskSuspend(myTask03Handle);
		OLED_Clear();
		vTaskResume(myTask04Handle);
		osDelay(3000);
  }
  /* USER CODE END OLED_ShowTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
