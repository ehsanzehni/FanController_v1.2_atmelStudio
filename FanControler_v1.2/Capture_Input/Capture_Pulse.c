/*
* Capture_Pulse.c
*
* Created: 3/5/2023 1:03:02 AM
*  Author: ehsan
*/

#define F_CPU 16000000UL
#include <stdio.h>
#include <avr/io.h>
#include "avr/interrupt.h"

#include "../SysTick/SysTick.h"
#include "Capture_Pulse.h"
#include "../ControlDevice/ControlDevice.h"



static  int a,b,c,high,period;
volatile static uint32_t printSys;

volatile static uint8_t counter_step ;
volatile static uint8_t countSamplingCapture;
static unsigned int duty_cycle;
static unsigned int final_dutycycle;
static unsigned int last_final_dutycycle;
static unsigned int Capture_Sampling;

static uint8_t check_intrrupt =1;

/*
*init the timer_1 for capture duty cycle of the pwm
*normal mode , no pres , noise cancell , intrupt enable
*/

void Capture_Pulde_Init()
{
	DDRB &=~(1<<0);
	PORTB &=~(1<<0);
	tccr1A_timer1 =0;
	tccr1B_timer1 |= (1<< ICNC1);
	printSys = get_Systick(); //count for the start capture
	
	
}

void Loop_Capture()
{
	if (get_Systick()>= printSys)
	{
		if (check_intrrupt == 1)
		{
		
				TCNT1=0;
				ICR1 =0;
				counter_step = step_1; // for the save status of the edge
				TIMSK |= (1<<TICIE1); //enable intrrupt capture timer_1
				TCCR1B |= (1<<ICES1)|(1<<CS10)|(1<< ICNC1);
				check_intrrupt = 0;
				sei();
		
		}
		else
		{
			if (PINB & (1<<0))
			{
				final_dutycycle = 100;
			}
			else 
			{
				final_dutycycle =0 ;
			}
		}
		printSys = get_Systick() + 3000;
	}
}

ISR(CAPTURE_ISR)
{
	cli();
	check_intrrupt = 1;
	if (counter_step == step_1)
	{
		a = ICR1;
		counter_step = step_2;
		TCCR1B &= ~(1<<ICES1);  //select failing edge
	}
	else if (counter_step == step_2 )
	{
		b = ICR1;
		counter_step = step_3;
		TCCR1B |= (1<<ICES1)|(1<<CS10)|(1<< ICNC1);//return to rising edge
	}
	else if (counter_step == step_3)
	{
		
		c = ICR1;
		TCCR1B = 0;
		
		if(a<b && b<c)
		{
			high=b-a;
			period=c-a;
			duty_cycle =((float)high /(float)period)*100;
			
			if (countSamplingCapture < 10)
			{
				countSamplingCapture++;
				Capture_Sampling += duty_cycle;
			}
			else if(countSamplingCapture == 10)
			{
				final_dutycycle = Capture_Sampling;
				last_final_dutycycle = final_dutycycle;
				countSamplingCapture = 0;
				Capture_Sampling = 0;
			}
			
}
else
{
	final_dutycycle = 200;
}
	}
	
sei();
}

uint8_t get_dutyCycle()
{
	if (final_dutycycle == 100)
	{
		return 100;
	}
	else if (final_dutycycle == 0)
	{
		return 0;
	}
	else
	{
		return (final_dutycycle / 10);
	}
}
