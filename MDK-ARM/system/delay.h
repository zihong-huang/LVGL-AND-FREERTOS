
#ifndef __DELAY_H
#define __DELAY_H


#include "main.h"

void tim1_init(void);
//void SysTick_Init(uint8_t SYSCLK); //SysTick��ʱ����ʼ������
void delay_us(uint32_t nus);       //΢�뼶��ʱ����
void delay_ms(uint16_t nms);       //���뼶��ʱ����
void delay_s(uint32_t s);

#endif
