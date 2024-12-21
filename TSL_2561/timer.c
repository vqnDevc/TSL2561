#include "timer.h"

void TIM2_Init(void) 
{
    /* enable clock cho timer2 */
	RCC->APB1ENR |= 0x01;
	/* Dat reload la gia tri cao nhat */
	TIM2->ARR |= 0xFFFF;
	/* Set gia tri cho thanh PSC de chia: 1 tick = fCLK/(PSC[15]-1) */
	TIM2->PSC = 71;
	TIM2->CR1 |= 0x01;
	TIM2->EGR |= 0x01;
}


void delay_us(uint32_t count)
{
	TIM2->CNT = 0;
	while(TIM2->CNT < count);
}

void delay_ms(uint32_t count)
{
	while(count)
	{
		delay_us(1000);
		count --;
	}
}
