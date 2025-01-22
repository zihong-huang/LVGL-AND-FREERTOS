#ifndef __WIFI_H
#define __WIFI_H

#include "main.h"

#include "FreeRTOS.h"
#include "task.h"


//连接阿里云
#define clientId		k23bqwsZzj4.lvgl|securemode=2\\,signmethod=hmacsha256\\,timestamp=1733417229468|
#define username		lvgl&k23bqwsZzj4
#define	passwd			6620bf2bf1b2d16a33f6d6a538757d6e6e1f30c323a296233e3aceaa7707ad01
#define mqttHostUrl	iot-06z00g8zd7nlxjz.mqtt.iothub.aliyuncs.com
#define ports				1883

// ESP8266 AT命令
#define ESP8266_RESTORE        "AT+RESTORE\r\n"
#define ESP8266_RESET          "AT+RST\r\n"
#define ESP8266_MODE_STA       "AT+CWMODE=1\r\n"  // 设置为 STA 模式
#define ESP8266_CONNECT_WIFI   "AT+CWJAP=\"%s\",\"%s\"\r\n"  // 连接到 Wi-Fi
#define ESP8266_CHECK_STATUS   "AT+CIPSTATUS\r\n"  // 查询 Wi-Fi 状态
#define ESP8266_CHECK_CWJAP   "AT+CWJAP?\r\n"  // 查询 连接 状态
#define ESP8266_CHECK_CIPSTA   "AT+CIPSTA?\r\n"  // 查询 IP 状态
#define ESP8266_CHECK_CWMAC   "AT+CIPSTAMAC?\r\n"  // 查询 MAC 状态
#define ESP8266_START_SERVER   "AT+CIPSERVER=1,80\r\n"  // 启动服务器
#define ESP8266_CONNECT_SERVER "AT+CIPSTART=\"TCP\",\"%s\",%d\r\n"  // 连接到服务器
#define ESP8266_SEND_DATA      "AT+CIPSEND=%d\r\n"  // 发送数据
#define ESP8266_CLOSE_CONN     "AT+CIPCLOSE\r\n"  // 关闭连接
#define ESP8266_SET_PASS_THROUGH_MODE "AT+CIPMODE=1\r\n"  // 开启透传模式
#define ESP8266_EXIT_PASS_THROUGH_MODE "AT+CIPMODE=0\r\n"  // 退出透传模式
#define ESP8266_MQTTUSERCFG			"AT+MQTTUSERCFG=0,1,\"NULL\",\"username\",\"passwd\",0,0,\"\"\r\n"
#define ESP8266_MQTTCLIENTID		"AT+MQTTCLIENTID=0,\"clientId\"\r\n"			
#define ESP8266_MQTTCONN  			"AT+MQTTCONN=0,\"mqttHostUrl\",ports,1\r\n"


// ESP8266 驱动任务的栈大小和优先级
#define ESP8266_TASK_STACK_SIZE 128
#define ESP8266_TASK_PRIORITY   tskIDLE_PRIORITY + 2

// 函数声明
void ESP8266_Reset(void);
void ESP8266_SetMode_STA(void);
void ESP8266_ConnectToWiFi(char *ssid, char *password);
void ESP8266_CheckStatus(void);
void ESP8266_ConnectToServer(char *ip, uint16_t port);
void ESP8266_SendData(char *data, uint16_t len);
void ESP8266_CloseConnection(void);
void ESP8266_SetPassThroughMode(void);  // 开启透传模式
void ESP8266_ExitPassThroughMode(void); // 退出透传模式




#endif
