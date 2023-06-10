/*
* Pid_motor.c
*
* Created: 2/19/2022 8:17:00 PM
*  Author: Gosh
*/

#define F_CPU 16000000UL

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>


#include "avr/interrupt.h"
#include "TriakRun.h"




static uint8_t Fan_Speed ;
static uint8_t motor_run_permission = 0;
inline void start_timer();
inline void stop_timer();
static uint8_t counter ;


void Init_Pid_Motor()
{
	
	Ddr_triac |= (1<<triac_position);
	inttrupt_register |= (1<<timer0_enable_inttrupt_bit);
	sei(); // enable intrupt
	
}


void Run_Sw_Timer()
{
stop_timer();
if (Fan_Speed == 0)
{
	if (motor_run_permission == 1)
	{
		Port_triac |= (1<<triac_position);
		_delay_us(2);
		Port_triac &= ~(1<<triac_position);
	}
}else
{
	counter =0;
	start_timer();
}
}

ISR(timer0_ISR)
{
	cli();
	stop_timer();
	if (counter < Fan_Speed)
	{
		counter ++;
		start_timer();
	}
	else if (counter == Fan_Speed)
	{
		
		counter =0;
		if (motor_run_permission == 1)
		{
			Port_triac |= (1<<triac_position);
			_delay_us(10);
			Port_triac &= ~(1<<triac_position);
		}
	}
	sei();
}

//**************************************seter************************
void Set_FanSpeed(uint8_t FanSpeed)
{
	Fan_Speed = FanSpeed;

}
void Set_FanPermission(uint8_t Permission)
{
	motor_run_permission = Permission;
}
inline void start_timer()
{
	Tccr0_timer0 |= (1<<CS01) | (1<<CS00);
}
inline void stop_timer()
{
	Tccr0_timer0 =0;
}