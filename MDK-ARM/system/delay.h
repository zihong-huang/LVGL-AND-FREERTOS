
#ifndef __DELAY_H
#define __DELAY_H


#include "main.h"

void tim1_init(void);
//void SysTick_Init(uint8_t SYSCLK); //SysTick定时器初始化函数
void delay_us(uint32_t nus);       //微秒级延时函数
void delay_ms(uint16_t nms);       //毫秒级延时函数
void delay_s(uint32_t s);

#endif
