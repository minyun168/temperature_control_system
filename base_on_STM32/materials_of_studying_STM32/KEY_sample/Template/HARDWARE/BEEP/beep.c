//#include "led.h"
#include "stm32f10x.h"
#include "beep.h"

void BEEP_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	//GPIO_Init(GPIOE,&GPIO_InitStructure);
	//GPIO_SetBits(GPIOE,GPIO_Pin_5);
	
	GPIO_Init(GPIOB,&GPIO_InitStructure); //PB8 is Beep
	GPIO_SetBits(GPIOB,GPIO_Pin_8);
}
