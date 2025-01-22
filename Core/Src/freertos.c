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
#include "wifi.h"
#include "lvgl.h"
#include "touch.h"
#include "my_gui.h"
#include "usart.h"
#include "flash.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
//lv_obj_t *led;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Task_LVGL */
osThreadId_t Task_LVGLHandle;
const osThreadAttr_t Task_LVGL_attributes = {
  .name = "Task_LVGL",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityLow1,
};
/* Definitions for LED1 */
osThreadId_t LED1Handle;
const osThreadAttr_t LED1_attributes = {
  .name = "LED1",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow1,
};
/* Definitions for task_wifi */
osThreadId_t task_wifiHandle;
const osThreadAttr_t task_wifi_attributes = {
  .name = "task_wifi",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow1,
};
/* Definitions for LVGL_Mutex */
osMutexId_t LVGL_MutexHandle;
const osMutexAttr_t LVGL_Mutex_attributes = {
  .name = "LVGL_Mutex"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void AppTask_LVGL(void *argument);
void Task_LED1(void *argument);
void ESP8266_Task(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationTickHook(void);

/* USER CODE BEGIN 3 */
void vApplicationTickHook( void )
{
   /* This function will be called by each tick interrupt if
   configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h. User code can be
   added here, but the tick hook is called from an interrupt context, so
   code must not attempt to block, and only the interrupt safe FreeRTOS API
   functions can be used (those that end in FromISR()). */
		lv_tick_inc(1);
}
/* USER CODE END 3 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* creation of LVGL_Mutex */
  LVGL_MutexHandle = osMutexNew(&LVGL_Mutex_attributes);

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
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of Task_LVGL */
  Task_LVGLHandle = osThreadNew(AppTask_LVGL, NULL, &Task_LVGL_attributes);

  /* creation of LED1 */
  LED1Handle = osThreadNew(Task_LED1, NULL, &LED1_attributes);

  /* creation of task_wifi */
  task_wifiHandle = osThreadNew(ESP8266_Task, NULL, &task_wifi_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_AppTask_LVGL */
/**
* @brief Function implementing the Task_LVGL thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_AppTask_LVGL */
void AppTask_LVGL(void *argument)
{
  /* USER CODE BEGIN AppTask_LVGL */
  /* Infinite loop */
	menu();
	
  for(;;)
  {
    /* ��ȡ�ź�����ȷ��LVGL�̰߳�ȫ */
//    if (xSemaphoreTake(LVGL_MutexHandle, portMAX_DELAY) == pdTRUE)
//    {
      TOUCH_Scan();          // ����ɨ��
      lv_task_handler();     // LVGL������
//      xSemaphoreGive(LVGL_MutexHandle); // �ͷ��ź���
//    }

    /* ��ʱ���ƣ�20msˢ��һ�� */
    vTaskDelay(pdMS_TO_TICKS(20));
  }
  /* USER CODE END AppTask_LVGL */
}

/* USER CODE BEGIN Header_Task_LED1 */
/**
* @brief Function implementing the LED1 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task_LED1 */
void Task_LED1(void *argument)
{
  /* USER CODE BEGIN Task_LED1 */
	
  /* Infinite loop */
  for(;;)
  {
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		
    osDelay(200);
  }
  /* USER CODE END Task_LED1 */
}

/* USER CODE BEGIN Header_ESP8266_Task */
/**
* @brief Function implementing the task_wifi thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ESP8266_Task */
void ESP8266_Task(void *argument)
{
  /* USER CODE BEGIN ESP8266_Task */
  /* Infinite loop */
	
	// ���� ESP8266
	ESP8266_Reset();
	
	// ���� ESP8266 Ϊ STA ģʽ
//	ESP8266_SetMode_STA();
	
	// ���ӵ� Wi-Fi ����
//	ESP8266_ConnectToWiFi("harmony", "11111111");

	// �������״̬
	ESP8266_CheckStatus();
	UART2_SendString(ESP8266_CHECK_CWJAP);
	vTaskDelay(pdMS_TO_TICKS(200)); 
	UART2_SendString(ESP8266_CHECK_CIPSTA);
	vTaskDelay(pdMS_TO_TICKS(1000)); 
	UART2_SendString(ESP8266_CHECK_CWMAC);
	vTaskDelay(pdMS_TO_TICKS(1000)); 
	UART2_SendString(ESP8266_MQTTUSERCFG);
	vTaskDelay(pdMS_TO_TICKS(2000)); 
	UART2_SendString(ESP8266_MQTTCLIENTID);
	vTaskDelay(pdMS_TO_TICKS(3000)); 
	UART2_SendString(ESP8266_MQTTCONN);
  vTaskDelay(pdMS_TO_TICKS(4000)); 
//	// ���ӵ������� (ʾ�������ӵ�ĳ�� IP ��ַ�Ͷ˿�)
//	ESP8266_ConnectToServer("192.168.31.25", 8080);
//	ESP8266_SetPassThroughMode();
//	while(EN25QXX_ReadID()!=EN25Q64)			//��ⲻ��EN25Q64
//	{
//		UART2_SendString("EN25Q64 Check Failed!\r\n");

//	}
//	UART2_SendString("EN25Q64 OK\r\n");
//	UART2_SendString("AT+UART=115200,8,1,0\r\n");
  for(;;)
  {
		// �������ݵ�������
//		char message[] = "Hello from STM32!";
//		ESP8266_SendData(message, strlen(message));
//		ESP8266_CheckStatus();
//		UART2_SendString(ESP8266_CHECK_CWJAP);
//		UART2_SendString(ESP8266_CHECK_CIPSTA);
//		UART2_SendString(ESP8266_CHECK_CWMAC);
		vTaskDelay(pdMS_TO_TICKS(200));  
  }
  /* USER CODE END ESP8266_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
//void event_cb(lv_event_t *e)
//{
//		lv_event_code_t code = lv_event_get_code(e);
//		if(code == LV_EVENT_CLICKED)
//		HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
//		lv_led_toggle(led);
//}
/* USER CODE END Application */

