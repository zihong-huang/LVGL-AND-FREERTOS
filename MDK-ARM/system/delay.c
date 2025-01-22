#include "delay.h"

//static uint32_t  fac_us=0;							//1us����fac_us����		   

///*******************************************************************************
//* �� �� ��:          SysTick_Init
//* ��������:          SysTick��ʼ������
//* ��    ��:          SYSCLK:ϵͳʱ��Ƶ��
//* ��    ��:          ��
//*******************************************************************************/
//void SysTick_Init(uint8_t SYSCLK)
//{
// 	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);//SysTickƵ��ΪHCLK 
//	fac_us=SYSCLK;						//����1us����ļ�������  
//}								    

///*************************************************
//*��������            Delay_us
//*�������ܣ�          ΢�뼶��ʱ����
//*���룺              nus����ʱnus΢��
//                     ע�⣺nus��ȡֵΪ0~190887435(���ֵ��2^32/fac_us@fac_us=22.5)
//*����ֵ��            ��
//**************************************************/	 
//void delay_us(uint32_t nus)
//{		
//	uint32_t ticks;
//	uint32_t told,tnow,tcnt=0;
//	uint32_t reload=SysTick->LOAD;				//LOAD��ֵ	    	 
//	ticks=nus*fac_us; 						//��Ҫ�Ľ����� 
//	told=SysTick->VAL;        				//�ս���ʱ�ļ�����ֵ
//	while(1)
//	{
//		tnow=SysTick->VAL;	
//		if(tnow!=told)
//		{	    
//			if(tnow<told)tcnt+=told-tnow;	//����ע��һ��SYSTICK��һ���ݼ��ļ������Ϳ�����.
//			else tcnt+=reload-tnow+told;	    
//			told=tnow;
//			if(tcnt>=ticks)break;			//ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�.
//		}  
//	};
//}

///*************************************************
//*��������            Delay_ms
//*�������ܣ�          ���뼶��ʱ����
//*���룺              nus����ʱnus����
//*����ֵ��            ��
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
    htim1.Init.Prescaler = (SystemCoreClock / 1000000) - 1;  // ���ö�ʱ��Ԥ��Ƶ��Ϊ1 MHz
    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim1.Init.Period = 0xFFFFFFFF;  // ������ֵ
    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim1.Init.RepetitionCounter = 0;

    HAL_TIM_Base_Init(&htim1);
    HAL_TIM_Base_Start(&htim1);  // ������ʱ��
}

void delay_us(uint32_t nus) {
    uint32_t startTick = __HAL_TIM_GET_COUNTER(&htim1);
    uint32_t delayTicks = nus;

    while ((__HAL_TIM_GET_COUNTER(&htim1) - startTick) < delayTicks);  // �ȴ��������ﵽ��ʱʱ��
}

void delay_ms(uint16_t nms) {
    delay_us(nms * 1000);  // ����ת��Ϊ΢�벢����΢�뼶��ʱ����
}

void delay_s(uint32_t s) {
    delay_ms(s * 1000);  // ��ת��Ϊ���벢���ú��뼶��ʱ����
}
