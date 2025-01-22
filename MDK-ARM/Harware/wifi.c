#include "wifi.h"
#include "usart.h"


// ESP8266 重启
void ESP8266_Reset(void) {
    UART2_SendString(ESP8266_RESET);
    vTaskDelay(pdMS_TO_TICKS(1000));  // 使用 FreeRTOS 延时
}

// 设置 ESP8266 为 STA 模式
void ESP8266_SetMode_STA(void) {
    UART2_SendString(ESP8266_MODE_STA);
    vTaskDelay(pdMS_TO_TICKS(2000));  // 设置为 STA 模式后等待 ESP8266 完成配置
}

// 连接到 Wi-Fi
void ESP8266_ConnectToWiFi(char *ssid, char *password) {
    char cmd[100];
    snprintf(cmd, sizeof(cmd), ESP8266_CONNECT_WIFI, ssid, password);
    UART2_SendString(cmd);
    vTaskDelay(pdMS_TO_TICKS(8000));  // 等待 5 秒钟连接 Wi-Fi
}

// 查询 ESP8266 状态
void ESP8266_CheckStatus(void) {
    UART2_SendString(ESP8266_CHECK_STATUS);
    vTaskDelay(pdMS_TO_TICKS(1000));  // 查询状态后等待响应
}

// 连接到服务器
void ESP8266_ConnectToServer(char *ip, uint16_t port) {
    char cmd[100];
    snprintf(cmd, sizeof(cmd), ESP8266_CONNECT_SERVER, ip, port);
    UART2_SendString(cmd);
    vTaskDelay(pdMS_TO_TICKS(7000));  // 等待连接服务器
}

// 发送数据到服务器
void ESP8266_SendData(char *data, uint16_t len) {
    char cmd[50];
    snprintf(cmd, sizeof(cmd), ESP8266_SEND_DATA, len);
    UART2_SendString(cmd);  // 发送数据长度
    vTaskDelay(pdMS_TO_TICKS(1000));  // 等待确认

    UART2_SendString(data);  // 发送实际的数据
    vTaskDelay(pdMS_TO_TICKS(1000));  // 等待数据发送完成
}

// 关闭连接
void ESP8266_CloseConnection(void) {
    UART2_SendString(ESP8266_CLOSE_CONN);
    vTaskDelay(pdMS_TO_TICKS(1000));  // 等待关闭连接
}

// 开启透传模式
void ESP8266_SetPassThroughMode(void) {
    UART2_SendString(ESP8266_SET_PASS_THROUGH_MODE);
    vTaskDelay(pdMS_TO_TICKS(1000));  // 等待透传模式开启
}

// 退出透传模式
void ESP8266_ExitPassThroughMode(void) {
    UART2_SendString(ESP8266_EXIT_PASS_THROUGH_MODE);
    vTaskDelay(pdMS_TO_TICKS(1000));  // 等待退出透传模式
}

//// ESP8266 操作任务
//void ESP8266_Task(void *pvParameters) {
//    // 重启 ESP8266
//    ESP8266_Reset();

//    // 设置 ESP8266 为 STA 模式
//    ESP8266_SetMode_STA();

//    // 连接到 Wi-Fi 网络
//    ESP8266_ConnectToWiFi("harmony", "huangzihong**-24");

//    // 检查连接状态
//    ESP8266_CheckStatus();

//    // 连接到服务器 (示例：连接到某个 IP 地址和端口)
//    ESP8266_ConnectToServer("192.168.31.230", 8080);
//		while(1)
//		{
//				// 发送数据到服务器
//				char message[] = "Hello from STM32!";
//				ESP8266_SendData(message, strlen(message));
//				vTaskDelay(pdMS_TO_TICKS(500));  
//		}
//    // 关闭连接
//    ESP8266_CloseConnection();

//    // 结束任务
//    vTaskDelete(NULL);
//}




