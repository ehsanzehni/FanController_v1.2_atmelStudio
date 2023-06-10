/*
* SysTick.c
*
* Created: 1/25/2022 2:35:54 AM
*  Author: Gosh
*/
#define F_CPU 16000000UL
#include "SysTick.h"
#include "SysTick_Config.h"
#include "avr/interrupt.h"

#include <avr/io.h>




volatile static uint32_t sysTick_timer2 = 0;





//******************high level method***************************
void SysTick_Init()
{
	Tccr_timer2 |= (1<<WGM21)|(1<<CS22);
	OCR_timer2 = 250; // set to up counting
	TIMSK |= (1<<Ocie_timer2);
	sei(); // enable intrupt
}

uint32_t get_Systick()
{
	return sysTick_timer2;
}



ISR(timer2_ISR)
{
	cli();
	sysTick_timer2 ++;
	sei();
	
}




