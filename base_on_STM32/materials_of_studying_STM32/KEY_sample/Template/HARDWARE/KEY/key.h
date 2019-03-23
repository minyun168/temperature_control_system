#ifndef __KEY_H
#define __KEY_H
#include "sys.h"

#define KEY0 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)
#define KEY1 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)
#define WK_UP GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)


#define KEY0_PRESS 1
#define KEY1_PRESS 2
#define WKUP_PRESS 3

void KEY_Init(void);
u8 KEY_Scan(u8);

#endif 