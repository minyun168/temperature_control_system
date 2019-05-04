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
	short Set_Temp=40; 
	short temperature;   
	short interval; 
	short count;	
	short i;   

	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ 115200
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();
	LCD_Init();			   	//��ʼ��LCD  
 	POINT_COLOR=GREEN;		//��������Ϊ��ɫ 
	LCD_ShowString(30,50,200,16,16,"2019/5/19");	
	//LCD_ShowString(30,70,200,16,16,"DS18B20 TEST");	
	POINT_COLOR=BLUE;     //��ɫ
	LCD_ShowString(30,90,200,16,16,"Set Temp:   C");
	//LCD_ShowString(30,110,200,16,16,"2019/5/19");		  
 	while(DS18B20_Init())	//DS18B20��ʼ��	
	{
		LCD_ShowString(30,130,200,16,16,"DS18B20 Error");
		delay_ms(200);
		LCD_Fill(30,130,239,130+16,WHITE);
 		delay_ms(200);
	}							
	POINT_COLOR=GREEN;
	LCD_ShowString(30,130,200,16,16,"DS18B20 OK");
	POINT_COLOR=RED;//��������Ϊ��ɫ 
 	LCD_ShowString(30,150,200,16,16,"Temp:   . C");	 
	while(1)
	{
		//if(KEY_Scan(0)==0)
			if(t%10==0)			//ÿ100ms��ȡһ��
			{									  
				temperature=DS18B20_Get_Temp();	
				/*if(temperature<0)
				{
					LCD_ShowChar(30+40,150,'-',16,0);			//��ʾ����
					temperature=-temperature;					//תΪ����
				}*/
				//else 
				//	LCD_ShowChar(30+40,150,' ',16,0);			//ȥ������
				LCD_ShowNum(30+48,150,temperature/10,2,16);	//��ʾ��������	    
				LCD_ShowNum(30+72,150,temperature%10,1,16);	//��ʾС������ 	
			}				   
			delay_ms(10);
			t++;
			if(t==20)
			{
				t=0;
			//	LED0=!LED0;
			}
			
			LCD_ShowNum(30+80,90,Set_Temp,2,16);	//��ʾ��������	    
			//LCD_ShowNum(30+72,90,Set_Temp%10,1,16);	//��ʾС������ 	
			
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
			
			interval=80;

			for(i=0;i<50;i++)
			{
				if((temperature/10+interval)<=100)
				{

					Set_Temp = temperature/10+interval;
					count=0;
					for(;count<900;count++)
					{					 	
						 if((Set_Temp*10)<=temperature)
						 {
							// delay_ms(890);			 
							 LED0=0;
							 delay_ms(1000);							 
						 }
						 else if((Set_Temp*10)>temperature)
						 {
						 	
						 	// delay_ms(500);
							 LED0=1;
							 delay_ms(1000);
							// LED0=0;							
						 }
						 LCD_ShowNum(30+80,90,Set_Temp,2,16);
						 temperature=DS18B20_Get_Temp();	
						 LCD_ShowNum(30+48,150,temperature/10,2,16);	    
				     LCD_ShowNum(30+72,150,temperature%10,1,16);	
						 
					}
		    }
				//interval=interval+5;

			 }	

			/* if (count==32760)
			 {
			 	count=0;
			 }	
			*/
	}
}
