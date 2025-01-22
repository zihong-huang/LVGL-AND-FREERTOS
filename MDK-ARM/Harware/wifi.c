#include "wifi.h"
#include "usart.h"


// ESP8266 ����
void ESP8266_Reset(void) {
    UART2_SendString(ESP8266_RESET);
    vTaskDelay(pdMS_TO_TICKS(1000));  // ʹ�� FreeRTOS ��ʱ
}

// ���� ESP8266 Ϊ STA ģʽ
void ESP8266_SetMode_STA(void) {
    UART2_SendString(ESP8266_MODE_STA);
    vTaskDelay(pdMS_TO_TICKS(2000));  // ����Ϊ STA ģʽ��ȴ� ESP8266 �������
}

// ���ӵ� Wi-Fi
void ESP8266_ConnectToWiFi(char *ssid, char *password) {
    char cmd[100];
    snprintf(cmd, sizeof(cmd), ESP8266_CONNECT_WIFI, ssid, password);
    UART2_SendString(cmd);
    vTaskDelay(pdMS_TO_TICKS(8000));  // �ȴ� 5 �������� Wi-Fi
}

// ��ѯ ESP8266 ״̬
void ESP8266_CheckStatus(void) {
    UART2_SendString(ESP8266_CHECK_STATUS);
    vTaskDelay(pdMS_TO_TICKS(1000));  // ��ѯ״̬��ȴ���Ӧ
}

// ���ӵ�������
void ESP8266_ConnectToServer(char *ip, uint16_t port) {
    char cmd[100];
    snprintf(cmd, sizeof(cmd), ESP8266_CONNECT_SERVER, ip, port);
    UART2_SendString(cmd);
    vTaskDelay(pdMS_TO_TICKS(7000));  // �ȴ����ӷ�����
}

// �������ݵ�������
void ESP8266_SendData(char *data, uint16_t len) {
    char cmd[50];
    snprintf(cmd, sizeof(cmd), ESP8266_SEND_DATA, len);
    UART2_SendString(cmd);  // �������ݳ���
    vTaskDelay(pdMS_TO_TICKS(1000));  // �ȴ�ȷ��

    UART2_SendString(data);  // ����ʵ�ʵ�����
    vTaskDelay(pdMS_TO_TICKS(1000));  // �ȴ����ݷ������
}

// �ر�����
void ESP8266_CloseConnection(void) {
    UART2_SendString(ESP8266_CLOSE_CONN);
    vTaskDelay(pdMS_TO_TICKS(1000));  // �ȴ��ر�����
}

// ����͸��ģʽ
void ESP8266_SetPassThroughMode(void) {
    UART2_SendString(ESP8266_SET_PASS_THROUGH_MODE);
    vTaskDelay(pdMS_TO_TICKS(1000));  // �ȴ�͸��ģʽ����
}

// �˳�͸��ģʽ
void ESP8266_ExitPassThroughMode(void) {
    UART2_SendString(ESP8266_EXIT_PASS_THROUGH_MODE);
    vTaskDelay(pdMS_TO_TICKS(1000));  // �ȴ��˳�͸��ģʽ
}

//// ESP8266 ��������
//void ESP8266_Task(void *pvParameters) {
//    // ���� ESP8266
//    ESP8266_Reset();

//    // ���� ESP8266 Ϊ STA ģʽ
//    ESP8266_SetMode_STA();

//    // ���ӵ� Wi-Fi ����
//    ESP8266_ConnectToWiFi("harmony", "huangzihong**-24");

//    // �������״̬
//    ESP8266_CheckStatus();

//    // ���ӵ������� (ʾ�������ӵ�ĳ�� IP ��ַ�Ͷ˿�)
//    ESP8266_ConnectToServer("192.168.31.230", 8080);
//		while(1)
//		{
//				// �������ݵ�������
//				char message[] = "Hello from STM32!";
//				ESP8266_SendData(message, strlen(message));
//				vTaskDelay(pdMS_TO_TICKS(500));  
//		}
//    // �ر�����
//    ESP8266_CloseConnection();

//    // ��������
//    vTaskDelete(NULL);
//}




