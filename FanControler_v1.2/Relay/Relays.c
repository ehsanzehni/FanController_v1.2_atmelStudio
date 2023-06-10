/*
* Relays.c
*
* Created: 2/20/2022 9:20:13 PM
*  Author: Gosh
*/
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "Relays.h"

#define ON 1
#define OFF 0


void Relays_Init()
{
	Ddr_Relay_1 |= (1<<Relay_1_Position);
	Port_Relay_1 &= ~(1<<Relay_1_Position);
}
void Relay_1_Target(uint8_t mode)
{
	if (mode == ON)
	{
		Port_Relay_1 |= (1<<Relay_1_Position);
	}
	else
	{
		Port_Relay_1 &= ~(1<<Relay_1_Position);
	}
}



