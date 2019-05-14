# temperature_control_system

part1:
	This system base on the chips of C51, adc0809, dac0832; 
	and it is applied to vegetable greenhouse.


part2:
	This system base on the chips of STM32F103ZET6, DS18B20, water bath heating device; 	
	and it is applied to water bath temperature control device.
	I have a paper about the water bath temperature control device, 
	and the code is for that.
	
	
## part2 have some bug

1. deviation is not complete，when the range of temperature between 6～9, above 11 degrees.
2. Sometime it happens, when temperature was falling above setting temperature 1 degree, it did not heating.


## part2 有一些bug尚待处理

1. 加热的偏差值未完善，主要还剩6-9摄氏度、11摄氏度及以上。
2. 温度低下来时，仍然采用原来的加热模式，并且偏差都为0.2了（这个bug似乎已经解决）
3. 小功率模式等的比较久，而且超过一摄氏度后还没再次加热
4. 为什么半功率模式温度下降时启用小功率模式的条件为设定的1摄氏度，而全功率为将近2摄氏度？


