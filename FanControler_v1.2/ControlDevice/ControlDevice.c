/*
* ControlDevice.c
*
* Created: 4/18/2023 12:31:16 AM
*  Author: ehsan
*/
#include <avr/io.h>
#include "ControlDevice.h"
#include "../Uart/uart.h"
#include "../Capture_Input/Capture_Pulse.h"
#include "../Motor_Controller/TriakRun.h"
#include "../SysTick/SysTick.h"
#include "../Sensor/Adc.h"
#include "../Relay/Relays.h"
#include "../ErrorSwitch/ErrorSwitch.h"
#include "../ErrorSwitch/ErrorLed.h"


Device_TypeDef Device = {0} ;
static uint8_t Sensor_Permision =0;
uint8_t error_detect = 0;
uint8_t count_error =0;
 char buffer[10] = {0};

volatile static uint32_t sys_fan;
volatile static uint32_t sys_sensor;
volatile static uint32_t sys_startTime;

uint8_t map_percent_to_step(uint8_t p);
static void temp_handler();
static void fan_ac_handler();


void Device_Init()
{
	Error_Switch_Init();
	init_Error_Led();
	//check sensor select
	if (PINC & (1<<5))
	{
		Sensor_Permision = 1;
	}else
	{
		Sensor_Permision = 0;
	}
	
	Device.status = NONE_ERROR;
	Device.sensor_num = NONE_ERROR;
	Device.mode = DEVICE_NORMAL_MODE;
	Set_FanPermission(1);
	sys_fan = get_Systick();
	sys_sensor = get_Systick();
	sys_startTime = get_Systick();
}
void Device_Loop()
{
	Error_Handler();
	switch(Device.mode)
	{
		case DEVICE_NORMAL_MODE:
		temp_handler();
		fan_ac_handler();
		Relay_1_Target(1);
		if (error_detect == 1)
		{
			error_detect =0;
			if (count_error >= 5)
			{
				Relay_1_Target(0);
				if (Device.status == OVER_TEMP_ERROR)
				{
					Set_FanSpeed(0);
				}else
				{
					Set_FanPermission(0);
				}
				count_error = 0;
				Device.mode = DEVICE_ERROR_MODE;
			}else
			{
				count_error +=1;
			}
			
		}
		break;
		case DEVICE_ERROR_MODE:
		
		  itoa( Device.status, buffer, 10);   // convert interger into string (decimal format)
		  uart_puts(buffer);        // and transmit string to UART
		    uart_puts("  ");     
		    itoa( Device.sensor_num, buffer, 10);   // convert interger into string (decimal format)
		    uart_puts(buffer);  
			  uart_puts("     ");           // and transmit string to UART
			  
		
		break;
	}
}

 uint8_t map_percent_to_step(uint8_t p)
{
	
	if ((p >= 0)&&(p <= 20))
	{
		return 4;
	}else if ((p >20)&&(p <= 30))
	{
		return 3;
	}else if ((p >30)&&(p <= 40))
	{
		return 2;
	}else if ((p >40)&&(p <= 50))
	{
		return 1;
	}else if ((p >50)&&(p <= 60))
	{
		return 0;
	}else if ((p >60)&&(p <= 70))
	{
		return 0;
	}else if ((p >70)&&(p <= 100))
	{
		return 0;
	}
	return 0;
}

static void temp_handler()
{
	if (get_Systick()>= sys_sensor)
	{
		if (Sensor_Permision == 1)
		{
			adc_handler();
			Device.Temp_1 = get_temp_0();
			Device.Temp_2 = get_temp_1();
			Device.Temp_3 = get_temp_2();
		
		itoa( Device.Temp_1, buffer, 10);   // convert interger into string (decimal format)
		uart_puts(buffer);        // and transmit string to UART
		uart_puts("  ");
		itoa( Device.Temp_2, buffer, 10);   // convert interger into string (decimal format)
		uart_puts(buffer);        // and transmit string to UART
		uart_puts("  ");
		itoa( Device.Temp_3, buffer, 10);   // convert interger into string (decimal format)
		uart_puts(buffer);        // and transmit string to UART
		uart_puts("  ");
		uart_puts("         ");
			if (((Device.Temp_1 == 0) ||(Device.Temp_2 == 0)||( Device.Temp_3 == 0))&&(sys_startTime + DELAY_TIME_ERROR_CHECK < get_Systick()))
			{
				error_detect = 1;
				Device.status = SENSOR_FAILURE;
				if (Device.Temp_1 == 0)
				{
					Device.sensor_num = SENSOR_1_ERROR;
				}else if (Device.Temp_2 == 0)
				{
					Device.sensor_num = SENSOR_2_ERROR;
				}else if (Device.Temp_3 == 0)
				{
					Device.sensor_num = SENSOR_3_ERROR;
				}
			}
			if (((Device.Temp_1 >= OVER_TEMP) ||(Device.Temp_2 >= OVER_TEMP)|| (Device.Temp_3 >=OVER_TEMP))&&(sys_startTime + DELAY_TIME_ERROR_CHECK < get_Systick()))
			{
				error_detect = 1;
				Device.status = OVER_TEMP_ERROR;
				if (Device.Temp_1 >= OVER_TEMP)
				{
					Device.sensor_num = SENSOR_1_ERROR;
				}else if (Device.Temp_2 >= OVER_TEMP)
				{
					Device.sensor_num = SENSOR_2_ERROR;
				}else if (Device.Temp_3 >= OVER_TEMP)
				{
					Device.sensor_num = SENSOR_3_ERROR;
				}
				
			}
			
		}
		sys_sensor = get_Systick() + 500;
	}
	
}
static void fan_ac_handler()
{
	if (get_Systick()>= sys_fan)
	{
		Loop_Capture();
		Device.DutyCycle = get_dutyCycle();
			itoa( Device.DutyCycle, buffer, 10);   // convert interger into string (decimal format)
			uart_puts(buffer);        // and transmit string to UART
			uart_puts("           ");
		Set_FanSpeed(map_percent_to_step(Device.DutyCycle));
		if ((Device.DutyCycle ==0 )&&(sys_startTime + DELAY_TIME_ERROR_CHECK < get_Systick()))
		{
			error_detect = 1;
			Device.status = PWM_BROKEN_ERROR;
		}
		sys_fan = get_Systick() + 1000;
	}
}
void Error_Clear()
{
	Set_FanPermission(1);
	error_detect = 0;
	sys_startTime = get_Systick();
	Device.status = NONE_ERROR;
	Device.Temp_1 = 0;
	Device.Temp_2 = 0;
	Device.Temp_3 = 0;
	Device.mode = DEVICE_NORMAL_MODE;
}