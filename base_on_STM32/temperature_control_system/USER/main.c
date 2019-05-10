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
	u8 sure_key=0;
	u8 mode=0;
	short Temp_range;
  vu8 key=0;	 
	short Set_Temp=40; 
	short temperature;   
	short interval; 
	short count;	
	short deviation_value;
	short i,j; 
  short deviation_list[11][10]={{9,9,8,7,5,3,2,1,0,0},{9,9,8,6,5,4,3,1,0,0},{10,9,9,7,6,3,2,1,0,0},{10,10,9,8,6,5,3,2,1,0},{33,31,30,29,28,26,21,17,15,6},{33,31,30,29,28,26,21,17,15,6},{33,31,30,29,28,26,21,17,15,6},{33,31,30,29,28,26,21,17,15,6},{33,31,30,29,28,26,21,17,15,6},{73,64,53,50,47,45,41,39,23,20},{73,64,53,50,47,45,41,39,23,20}};	 

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
			while(sure_key==0)
			{
				key = KEY_Scan(0);
				if(key)
				{
					switch(key)
					{
						case WKUP_PRES:
							sure_key=1;
							//Set_Temp = 70;
							break;
						case KEY1_PRES:
							Set_Temp = Set_Temp+1;
							break;
						case KEY0_PRES:
							Set_Temp = Set_Temp-1;
							break;					
				  }
			 	 }
		   }

		   Temp_range = Set_Temp*10-temperature;  //difference between the range of Temp_range
			 
			 if(Temp_range>=1&&Temp_range<5)
			 {
				 delay_ms(900);
				 LED0=1;
				 delay_ms(100);
				 LED0=0;	
				 mode=1;
			 }
			 
			 else if (Temp_range>=5&&Temp_range<10)
			 {
				 delay_ms(500);
				 LED0=1;
				 delay_ms(500);
				 LED0=0;
				 mode=2;
			 }
			 
			 else if (Temp_range>=10)
			 {
				 LED0=1;
				 delay_ms(1000);
				 mode=3;
			 }
			 
			 else 
			 {
				 delay_ms(100);
			 }
			 
			 temperature=DS18B20_Get_Temp();	
			 LCD_ShowNum(30+48,150,temperature/10,2,16);	//显示正数部分	    
			 LCD_ShowNum(30+72,150,temperature%10,1,16);	//显示小数部分 	
			 LCD_ShowNum(30+80,90,Set_Temp,2,16);
			 
			 //sure i 
			 i=Temp_range-1;
			 //sure j
			 switch(temperature/10)
			 {
				 case 0: j=0;break;
				 case 1: j=1;break;
				 case 2: j=2;break;
				 case 3: j=3;break;
				 case 4: j=4;break;
				 case 5: j=5;break;
				 case 6: j=6;break;
				 case 7: j=7;break;
				 case 8: j=8;break;
				 case 9: j=9;break;
				 default: LCD_ShowString(30,130,200,16,16,"Have Error");
				 
			 }
			 
			 if(mode)
				{
					switch(mode)
					{
						case 1:
							
							deviation_value=deviation_list[i][j];
							break;
						case 2:
							//Set_Temp = Set_Temp+1;
							break;
						case 3:
							//Set_Temp = Set_Temp-1;
							break;					
				  }
			 	 }
				
				//
				if(Set_Temp>
			 
			 
			 
			 /*
			interval=1;

			for(i=0;i<100;i++)
			{
				if((temperature/10+interval)<=100)
				{

					Set_Temp = temperature/10+interval;
					count=0;
					for(;count<300;count++)
					{					 	
						 if((Set_Temp*10)<=temperature)
						 {
							// delay_ms(890);			 
							 LED0=0;
							 delay_ms(1000);							 
						 }
						 else if((Set_Temp*10)>temperature)
						 {
						 	
						 	 delay_ms(900);
							 LED0=1;
							 delay_ms(100);
							 LED0=0;							
						 }
						 LCD_ShowNum(30+80,90,Set_Temp,2,16);
						 temperature=DS18B20_Get_Temp();	
						 LCD_ShowNum(30+48,150,temperature/10,2,16);	    
				     LCD_ShowNum(30+72,150,temperature%10,1,16);	
						 
					}
		    }
				interval=interval+1;
				if(interval>5)
				{
					interval=1;
				}

			 }	

			 if (count==32760)
			 {
			 	count=0;
			 }	
			*/
	}
}
