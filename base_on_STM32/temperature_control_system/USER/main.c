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
	short Set_Temp; 
	short temperature;   
	short interval; 
	short count;	
	short deviation_value;
	short i=0,j=0; 
    short deviation_list[11][10]={{9,9,8,7,5,3,2,1,0,0},{9,9,8,6,5,4,3,1,0,0},{10,9,9,7,6,3,2,1,0,0},{10,10,9,8,6,5,3,2,1,0},{33,31,30,29,28,26,21,17,15,6},{33,31,30,29,28,26,21,17,15,6},{33,31,30,29,28,26,21,17,15,6},{33,31,30,29,28,26,21,17,15,6},{33,31,30,29,28,26,21,17,15,6},{73,64,53,50,47,45,41,39,23,20},{73,64,53,50,47,45,41,39,23,20}};	 

	delay_init();	    	 //ÑÓÊ±º¯Êý³õÊ¼»¯	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//ÉèÖÃÖÐ¶ÏÓÅÏÈ¼¶·Ö×éÎª×é2£º2Î»ÇÀÕ¼ÓÅÏÈ¼¶£¬2Î»ÏìÓ¦ÓÅÏÈ¼¶
	uart_init(115200);	 	//´®¿Ú³õÊ¼»¯Îª 115200
	LED_Init();		  		//³õÊ¼»¯ÓëLEDÁ¬½ÓµÄÓ²¼þ½Ó¿Ú
	KEY_Init();
	LCD_Init();			   	//³õÊ¼»¯LCD  
 	POINT_COLOR=GREEN;		//ÉèÖÃ×ÖÌåÎªÂÌÉ« 
	LCD_ShowString(30,50,200,16,16,"2019/5/19");	
	//LCD_ShowString(30,70,200,16,16,"DS18B20 TEST");	
	POINT_COLOR=BLUE;     //À¶É«
	LCD_ShowString(30,90,200,16,16,"Set Temp:   C");
	//LCD_ShowString(30,110,200,16,16,"2019/5/19");		  
 	while(DS18B20_Init())	//DS18B20³õÊ¼»¯	
	{
		LCD_ShowString(30,130,200,16,16,"DS18B20 Error");
		delay_ms(200);
		LCD_Fill(30,130,239,130+16,WHITE);
 		delay_ms(200);
	}							
	POINT_COLOR=GREEN;
	LCD_ShowString(30,130,200,16,16,"DS18B20 OK");
	POINT_COLOR=RED;//ÉèÖÃ×ÖÌåÎªºìÉ« 
 	LCD_ShowString(30,150,200,16,16,"Temp:   . C");	 
	while(1)
	{
		//if(KEY_Scan(0)==0)
			//if(t%10==0)			//Ã¿100ms¶ÁÈ¡Ò»´Î
			//{									  
				temperature=DS18B20_Get_Temp();	
				/*if(temperature<0)
				{
					LCD_ShowChar(30+40,150,'-',16,0);			//ÏÔÊ¾¸ººÅ
					temperature=-temperature;					//×ªÎªÕýÊý
				}*/
				//else 
				//	LCD_ShowChar(30+40,150,' ',16,0);			//È¥µô¸ººÅ
				LCD_ShowNum(30+48,150,temperature/10,2,16);	//ÏÔÊ¾ÕýÊý²¿·Ö	    
				LCD_ShowNum(30+72,150,temperature%10,1,16);	//ÏÔÊ¾Ð¡Êý²¿·Ö 	
			//}				   
			delay_ms(10);
			//t++;
			/*if(t==20)
			{
				t=0;
			//	LED0=!LED0;
			}
			*/
			//Set_Temp is 2 digit number,but temperature is 3 digit number
			Set_Temp=temperature/10;
			LCD_ShowNum(30+80,90,Set_Temp,2,16);	//ÏÔÊ¾ÕýÊý²¿·Ö	    
			//LCD_ShowNum(30+72,90,Set_Temp%10,1,16);	//ÏÔÊ¾Ð¡Êý²¿·Ö 	
			
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
			 	LCD_ShowNum(30+80,90,Set_Temp,2,16);
		    }


		while(1)
		{
		    Temp_range = Set_Temp*10-temperature;  //have *10  !!!!!!!!!!!!!!!!!!!!!!!!!!!
			 
			 if((Temp_range>=10)&&(Temp_range<50))
			 {
				 delay_ms(900);
				 LED0=1;
				 delay_ms(100);
				 LED0=0;	
				 mode=1;
			 }
			 
			 else if ((Temp_range>=50)&&(Temp_range<100))
			 {
				 delay_ms(500);
				 LED0=1;
				 delay_ms(500);
				 LED0=0;
				 mode=2;
			 }
			 
			 else if (Temp_range>=100)
			 {
				 LED0=1;
				 delay_ms(1000);
				 LED0=0;
				 mode=3;
			 }
			 
			 else 
			 {
				 delay_ms(100);
			 }
			 
			 temperature=DS18B20_Get_Temp();	
			 LCD_ShowNum(30+48,150,temperature/10,2,16);	//ÏÔÊ¾ÕýÊý²¿·Ö	    
			 LCD_ShowNum(30+72,150,temperature%10,1,16);	//ÏÔÊ¾Ð¡Êý²¿·Ö 	
			 LCD_ShowNum(30+80,90,Set_Temp,2,16);
			 
			 //sure i 
			 if(i<=0)
		 	 {
		 		i=i;
		 
			 }
			 else
			 {
			 	i=Temp_range-1;
			 }
			 //sure j
			 switch(temperature/100)
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
							deviation_value=deviation_list[i][j];
							//Set_Temp = Set_Temp+1;
							break;
						case 3:
							deviation_value=deviation_list[10][j];
							//Set_Temp = Set_Temp-1;
							break;					
				    }
			 	}
				
			
			//
			while((Set_Temp*10)>(temperature+deviation_value))
			{
				if(mode==1)
				{
					 delay_ms(900);
					 LED0=1;
					 delay_ms(100);
					 LED0=0;	

				}

				else if (mode==2)
				{
					delay_ms(500);
					LED0=1;
					delay_ms(500);
				    LED0=0;	
				}
				else if(mode==3)
				{
					LED0=1;
				    delay_ms(1000);
				    LED0=0;
				   // mode=3;
				}

				temperature=DS18B20_Get_Temp();	
			    LCD_ShowNum(30+48,150,temperature/10,2,16);	//ÏÔÊ¾ÕýÊý²¿·Ö	    
			    LCD_ShowNum(30+72,150,temperature%10,1,16);

			}




				//
			if((Set_Temp*10) <= (temperature + deviation_value))
			{
				if(mode==1)
				{
					delay_ms(1000);
					
				}
				else if(mode==2)
				{
					for(count=0;count<180;count++)
					{		
						delay_ms(1000);
					}


				}
				else if(mode==3)
				{
					for(count=0;count<300;count++)
						{
							delay_ms(1000);
						}
				}
				else 
				{


					delay_ms(1000);
					//LCD_ShowString(30,130,200,16,16,"Have not ");

				}
				//It is that enough?????
			}
			//when loop?????????
		}

			 
			 
			 
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
