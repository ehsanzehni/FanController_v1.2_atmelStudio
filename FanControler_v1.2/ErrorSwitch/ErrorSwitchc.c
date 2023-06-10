/*
 * ErrorSwitchc.c
 *
 * Created: 4/25/2023 9:29:32 PM
 *  Author: ehsan
 */ 
#include <stdio.h>
#include <avr/io.h>

#include "avr/interrupt.h"
#include "ErrorSwitch.h"
#include "../ControlDevice/ControlDevice.h"
#include "../Motor_Controller/TriakRun.h"

void Error_Switch_Init()
{
	
	switch_DDR &= ~(1<<switch_Position);
	Enable_Interrupt_SWITCH |= (1<<int_Mode_Switch);
	EXT_INT_STATUS_REGISTER_SWITCH |= (1<<ISC11)|(1<<ISC10);
	sei();
}

ISR (isr_mode_Switch)
{
	Error_Clear();
}
