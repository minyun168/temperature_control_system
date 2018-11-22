#include <REG51.H>      
#include <absacc.h>
#include <math.h>
#define ADC0809  0xCFA0             //AD数据采集口
#define DATA8279 0xCFE8             //8279的数据端口
#define CON8279  0xCFE9             //8279的控制口地址
#define DA0832OUT	0xCFB0	        //0832的数据口地址
typedef unsigned char uchar;
typedef unsigned int   uint;
uchar   T,Data;
uchar	ANJIAN;
uchar	YUZHI=25;                      //初始阈值为25
LED[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f}; 				
									    //数组表示八段数码管0-9的显示
void  delay(uchar i)						//子函数delay，延时
{
    uchar j=0;
	for(;i>0;i--)
	for(j=0;j<60;j++); 
}

uchar Readkey(void)						//子函数Readkey，读取键值
{
  uchar j;
  if(XBYTE[CON8279] & 0x07)    					
  {
    XBYTE[CON8279]=0x40;    							
    j=XBYTE[DATA8279]; 
    j=j-191;                        	     //191表示0键的值  					 
    return (j);               
  }
  return 0;}


void main()
{      
	 XBYTE[ADC0809]=0;          
	 XBYTE[CON8279]=0;       
	 XBYTE[CON8279]=0xD1;        
   	 while(XBYTE[CON8279]&0x80);      								  
	 XBYTE[DATA8279]=0x2A;            //初始化，键盘开始工作
	 while(1)
	 {
		
    	Data=XBYTE[ADC0809];          //0809测出来的电压
    	XBYTE[ADC0809]=0;
		T=(Data*20-1179)/52;
	  //T=1180080/(3275.706+686.294*log10(2530/Data-10))-273.15; 			
      //根据测出来的电压换算出的当前温度值
     	
		
		XBYTE[CON8279]=0x81;   				//选中第二个数码管  
		 XBYTE[DATA8279]=LED[T%10];			//显示十位
		XBYTE[CON8279]=0x80;
		 XBYTE[DATA8279]=LED[T/10];
		XBYTE[CON8279]=0x84;        		
		 XBYTE[DATA8279]=LED[YUZHI/10%10];
		XBYTE[CON8279]=0x85;
		 XBYTE[DATA8279]=LED[YUZHI%10];        
		 
		   delay(100);   
		    
		 ANJIAN=Readkey();   	                //调整阈值程序部分
		 if(ANJIAN!=0)
		 {
			 if(ANJIAN==1)
				{
          		YUZHI++;           			//按键1增加阈值
          		if(YUZHI>=35)
          		YUZHI=35;
                }    						//当阈值大于35的时候，阈值为35，显示为35
			 else if(ANJIAN==2)   
				{
           		YUZHI--;    					//按键2减小阈值
           		if(YUZHI<=15)
           		YUZHI=15;
                }
		 }  				   					 //当阈值小于15的时候，阈值为15，显示为15
		 

		 if(T<=15)
		 {  XBYTE[0xcfb0]=0;											 
		    XBYTE[0xcfb1]=0;
			P1=0xff;
		 }        				
											//当温度小于15的时候，只显示阈值，风扇不转
		 if(15<T&&T<YUZHI)
		 {  XBYTE[0xcfb0]=T*1;												  
		    XBYTE[0xcfb1]=T*1;
		    P1=0x55;	 			//绿灯亮
		 }          
 								//当温度大于15小于阈值的时候，显示当前温度和阈值，慢转
		 if(T>YUZHI&&T<50)
		 {	
	        XBYTE[0xcfb0]=(T-15)*7;												  
		    XBYTE[0xcfb1]=(T-15)*7;
		    P1=0xaa;           	//红灯亮
								//当温度大于阈值但是小于50的时候，显示温度，快转
		 }
		 if(T>50)
		 {	
		 	XBYTE[0xcfb0]=(T-15)*7;												  
		    XBYTE[0xcfb1]=(T-15)*7;
	        P1=0x00;    			//当温度大于50的时候，报警，全部灯亮
		 }
		   
	 }
}
