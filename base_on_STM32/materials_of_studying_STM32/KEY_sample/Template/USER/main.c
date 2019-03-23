#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "beep.h"
#include "sys.h"
#include "key.h"

int main(void)
{
	vu8 key=0;
	delay_init();
	BEEP_Init();
	LED_Init();
	KEY_Init();
	LED0 = 1;
	LED1 = 1;
	BEEP = 0;
	
	while(1)
	{
		key = KEY_Scan(0);
		if(key)
		{
			switch(key)
			{
				case WKUP_PRESS:
					BEEP = !BEEP;
					break;
				case KEY1_PRESS:
					LED1 = !LED1;
				  break;
				case KEY0_PRESS:
					LED0 = !LED0;
				  break;
					
			}
		}
		else delay_ms(10);
	}
}
