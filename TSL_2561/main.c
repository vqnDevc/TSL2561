#include "stm32f10x.h"
#include "TSL_Init.h"
#include "timer.h"
#include "filter.h"

volatile static float light;
volatile static float light_kalman;

volatile static uint16_t l0;
volatile static uint16_t l1;

volatile static uint16_t time;

int main()
{
	I2C_Config();
	TSL2561_Init();
	TIM2_Init();
	
	while(1)
	{
		TIM2->CNT = 0;
		light = TSL2561_ReadLight();
		time = TIM2->CNT;
		
		light_kalman = kalman_single((float)light, 10, 1);

		/*
		l0 = Read_0();
		l1 = Read_1();
		*/
		
		delay_ms(50);
	}
	
}
