#include "delay.h"

//static uint32_t  fac_us=0;							//1us计数fac_us个数		   

///*******************************************************************************
//* 函 数 名:          SysTick_Init
//* 函数功能:          SysTick初始化函数
//* 输    入:          SYSCLK:系统时钟频率
//* 输    出:          无
//*******************************************************************************/
//void SysTick_Init(uint8_t SYSCLK)
//{
// 	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);//SysTick频率为HCLK 
//	fac_us=SYSCLK;						//保存1us所需的计数次数  
//}								    

///*************************************************
//*函数名：            Delay_us
//*函数功能：          微秒级延时函数
//*输入：              nus：延时nus微秒
//                     注意：nus的取值为0~190887435(最大值即2^32/fac_us@fac_us=22.5)
//*返回值：            无
//**************************************************/	 
//void delay_us(uint32_t nus)
//{		
//	uint32_t ticks;
//	uint32_t told,tnow,tcnt=0;
//	uint32_t reload=SysTick->LOAD;				//LOAD的值	    	 
//	ticks=nus*fac_us; 						//需要的节拍数 
//	told=SysTick->VAL;        				//刚进入时的计数器值
//	while(1)
//	{
//		tnow=SysTick->VAL;	
//		if(tnow!=told)
//		{	    
//			if(tnow<told)tcnt+=told-tnow;	//这里注意一下SYSTICK是一个递减的计数器就可以了.
//			else tcnt+=reload-tnow+told;	    
//			told=tnow;
//			if(tcnt>=ticks)break;			//时间超过/等于要延迟的时间,则退出.
//		}  
//	};
//}

///*************************************************
//*函数名：            Delay_ms
//*函数功能：          毫秒级延时函数
//*输入：              nus：延时nus毫秒
//*返回值：            无
//**************************************************/	
//void delay_ms(uint16_t nms)
//{
//	uint32_t i;
//	for(i=0;i<nms;i++) delay_us(1000);
//}

TIM_HandleTypeDef htim1;

void tim1_init(void) {
    __HAL_RCC_TIM1_CLK_ENABLE();

    htim1.Instance = TIM6;
    htim1.Init.Prescaler = (SystemCoreClock / 1000000) - 1;  // 设置定时器预分频器为1 MHz
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = 0xFFFFFFFF;  // 最大计数值
    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim1.Init.RepetitionCounter = 0;

    HAL_TIM_Base_Init(&htim1);
    HAL_TIM_Base_Start(&htim1);  // 启动定时器
}

void delay_us(uint32_t nus) {
    uint32_t startTick = __HAL_TIM_GET_COUNTER(&htim1);
    uint32_t delayTicks = nus;

    while ((__HAL_TIM_GET_COUNTER(&htim1) - startTick) < delayTicks);  // 等待计数器达到延时时间
}

void delay_ms(uint16_t nms) {
    delay_us(nms * 1000);  // 毫秒转化为微秒并调用微秒级延时函数
}

void delay_s(uint32_t s) {
    delay_ms(s * 1000);  // 秒转化为毫秒并调用毫秒级延时函数
}
