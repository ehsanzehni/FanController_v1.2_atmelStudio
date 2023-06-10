/*
 * FanControler_v1.2.c
 *
 * Created: 1/12/2023 12:41:56 AM
 * Author : ehsan
 */ 

#define F_CPU 16000000UL
#define UART_BAUD_RATE   9600   

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>

#include "Relay/Relays.h"
#include "SysTick/SysTick.h"
#include "Zero_Crossing/Zero_Crossing.h"
#include "Sensor/Adc.h"
#include "Uart/uart.h"
#include "Capture_Input/Capture_Pulse.h"
#include "ControlDevice/ControlDevice.h"
#include "Motor_Controller/TriakRun.h"

int main(void)
{
	
	SysTick_Init();
	Relays_Init();
	Zero_Crossing_Init();
	Adc_Init();
	uart_init(UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU)); 
	Capture_Pulde_Init();
	Init_Pid_Motor();
	Device_Init();

	WDTCR |= (1<<WDE);
	
    while (1) 
    {
	wdt_reset();
	Device_Loop();
	}

}