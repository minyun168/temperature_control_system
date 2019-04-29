#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "ds18b20.h" 
 
 int main(void)
 {	 
	u8 t=0;	
  vu8 key=0;	 
	short Set_Temp=20; 
	short temperature;    	   

	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为 115200
	LED_Init();		  		//初始化与LED连接的硬件接口
	KEY_Init();
	LCD_Init();			   	//初始化LCD  
 	POINT_COLOR=GREEN;		//设置字体为绿色 
	LCD_ShowString(30,50,200,16,16,"2019/5/19");	
	//LCD_ShowString(30,70,200,16,16,"DS18B20 TEST");	
	POINT_COLOR=BLUE;     //蓝色
	LCD_ShowString(30,90,200,16,16,"Set Temp:   C");
	//LCD_ShowString(30,110,200,16,16,"2019/5/19");		  
 	while(DS18B20_Init())	//DS18B20初始化	
	{
		LCD_ShowString(30,130,200,16,16,"DS18B20 Error");
		delay_ms(200);
		LCD_Fill(30,130,239,130+16,WHITE);
 		delay_ms(200);
	}							
	POINT_COLOR=GREEN;
	LCD_ShowString(30,130,200,16,16,"DS18B20 OK");
	POINT_COLOR=RED;//设置字体为红色 
 	LCD_ShowString(30,150,200,16,16,"Temp:   . C");	 
	while(1)
	{
		//if(KEY_Scan(0)==0)
			if(t%10==0)			//每100ms读取一次
			{									  
				temperature=DS18B20_Get_Temp();	
				/*if(temperature<0)
				{
					LCD_ShowChar(30+40,150,'-',16,0);			//显示负号
					temperature=-temperature;					//转为正数
				}*/
				//else 
				//	LCD_ShowChar(30+40,150,' ',16,0);			//去掉负号
				LCD_ShowNum(30+48,150,temperature/10,2,16);	//显示正数部分	    
				LCD_ShowNum(30+72,150,temperature%10,1,16);	//显示小数部分 	
			}				   
			delay_ms(10);
			t++;
			if(t==20)
			{
				t=0;
			//	LED0=!LED0;
			}
			
			LCD_ShowNum(30+80,90,Set_Temp,2,16);	//显示正数部分	    
			//LCD_ShowNum(30+72,90,Set_Temp%10,1,16);	//显示小数部分 	
			
			//key0 - , key1 + , key_up return 70 
			key = KEY_Scan(0);
			if(key)
			{
				switch(key)
				{
					case WKUP_PRES:
						Set_Temp = 70;
						break;
					case KEY1_PRES:
						Set_Temp = Set_Temp+1;
						break;
					case KEY0_PRES:
						Set_Temp = Set_Temp-1;
						break;					
				}
			}
			 if((Set_Temp*10)<temperature)
			 {
				 //delay_ms(890);			 
				 LED0=0;
				 //delay_ms(100);
				 
			 }
			 else if((Set_Temp*10)>temperature-11)
			 {
				 delay_ms(890);
				 LED0=1;
				 delay_ms(100);
				 LED0=0;
			 }					
	}
}

