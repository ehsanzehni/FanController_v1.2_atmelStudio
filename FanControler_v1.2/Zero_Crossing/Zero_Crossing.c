/*
* zero_crossing.c
*
* Created: 2/15/2022 6:23:49 PM
*  Author: Gosh
*/
#define F_CPU 8000000UL






#include "Zero_Crossing.h"
#include "Zero_Crossing_Config.h"
#include "../Motor_Controller/TriakRun.h"


#include <stdio.h>
#include <avr/io.h>

#include "avr/interrupt.h"


void Zero_Crossing_Init()
{
	
	zero_DDR &= ~(1<<Z_Position);
	Enable_Interrupt_Zero |= (1<<int_Mode_Zero);
	EXT_INT_STATUS_REGISTER_Zero |= (1<<ISC00)|(1<<ISC01);
	sei();
}

ISR (isr_mode_Zero)
{
	cli();
	Run_Sw_Timer();
	sei();
}
