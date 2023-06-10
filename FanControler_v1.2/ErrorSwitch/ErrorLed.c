/*
 * ErrorLed.c
 *
 * Created: 4/26/2023 1:02:42 PM
 *  Author: ehsan
 */ 
#include "ErrorLed.h"
#include "../SysTick/SysTick.h"
#include "../ControlDevice/ControlDevice.h"
#include "../Uart/uart.h"

#define ON 1
#define OFF 0

#define start 0
#define start_2 1
#define start_3 2
#define stop 3
#define stop_2 4
#define stop_3 5
#define delay 6


#define delay_3 5
#define delay_4 6
volatile static uint32_t Led_sys;
volatile static uint8_t counter;

void Error_Led_Target(uint8_t mode);

void init_Error_Led()
{
	Error_Led_DDR |= (1<<Error_Led_Posion);
	Error_Led_PORT &= ~(1<<Error_Led_Posion);
	Led_sys = get_Systick();
	counter = start;
}

void Error_Handler()
{
	switch(Device.status)
	{
		case NONE_ERROR:
	
			Error_Led_Target(ON);
		break;
		case PWM_BROKEN_ERROR:
			if (get_Systick() >= Led_sys)
			{
				switch(counter)
				{
					case start:
					Error_Led_Target(ON);
					counter = stop;
					break;
					case stop:
					Error_Led_Target(OFF);
					counter =delay;
					break;
					case delay:
					counter = start;
					break;
				}
				
				Led_sys = get_Systick() + 1000;
			}
		break;
		case OVER_TEMP_ERROR:
			if (get_Systick() >= Led_sys)
			{
				switch(counter)
				{
					case start:
					Error_Led_Target(ON);
					counter = stop;
					break;
					case stop:
					Error_Led_Target(OFF);
					counter = start_2;
					break;
					case start_2:
					Error_Led_Target(ON);
					counter = stop_2;
					break;
					case stop_2:
					Error_Led_Target(OFF);
					counter = delay;
					break;
					case delay:
					counter = start;
					break;
				}
				Led_sys = get_Systick() + 1000;
			}
		break;
		
		case SENSOR_FAILURE:
			if (get_Systick() >= Led_sys)
			{
				switch(counter)
				{
					case start:
					Error_Led_Target(ON);
					counter = stop;
					break;
					case stop:
					Error_Led_Target(OFF);
					counter = start_2;
					break;
					case start_2:
					Error_Led_Target(ON);
					counter = stop_2;
					break;
					case stop_2:
					Error_Led_Target(OFF);
					counter = start_3;
					break;
					case start_3:
					Error_Led_Target(ON);
					counter = stop_3;
					break;
					case stop_3:
					Error_Led_Target(OFF);
					counter = delay;
					break;
					case delay:
					counter = start;
					break;
				}
				Led_sys = get_Systick() + 1000;
			}
			
		break;
	}
}
void Error_Led_Target(uint8_t mode)
{
	if (mode == ON)
	{
		Error_Led_PORT |= (1<<Error_Led_Posion);
	}
	else
	{
		Error_Led_PORT &= ~(1<<Error_Led_Posion);
	}
}