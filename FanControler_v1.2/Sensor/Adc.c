/*
 * Adc.c
 *
 * Created: 1/21/2023 1:02:11 AM
 *  Author: ehsan
 */ 


#include "Adc.h"
#include "../SysTick/SysTick.h"
#include "avr/interrupt.h"

#include <avr/io.h>
#include <math.h>





static double temp_0 = 0;
static double temp_0_0 = 0;
static uint16_t temp_0_Sampling = 0;
static double temp_1 = 0;
static double temp_1_1 = 0;
static uint16_t temp_1_Sampling = 0;
static double temp_2 = 0;
static double temp_2_2 = 0;
static uint16_t temp_2_Sampling = 0;

static uint8_t countSamplingTemp0 = 0;
static uint8_t countSamplingTemp1 = 0;
static uint8_t countSamplingTemp2 = 0;

static volatile uint32_t adc_timer_handler;
static volatile uint32_t refresh_data_timer;



void Adc_Init()
{
	AdcControlStatusRegister = 0b00001111;
	adc_timer_handler = get_Systick();
	Adc_Permission = 0;
	Adc_Status = FLAG_ADC_FREE;
	
}

void Read_Adc(uint8_t channel)
{
	switch(channel)
	{
		case 0:
		AdcMultiplexerSelectionRegister = 0b01000000;
		Adc_Status = FLAG_ADC_0;
		Adc_Permission = 1;
		break;
		case 1:
		AdcMultiplexerSelectionRegister = 0b01000001;
		Adc_Status = FLAG_ADC_1;
		Adc_Permission = 1;
		break;
		case 2:
		AdcMultiplexerSelectionRegister = 0b01000010;
		Adc_Status = FLAG_ADC_2;
		Adc_Permission = 1;
		break;
	}
		AdcControlStatusRegister |= (1<<Turning);
		AdcControlStatusRegister |= (1<<StartConversion);
}


ISR(Adc_ISR)
{
	switch(Adc_Status)
	{
		
		case FLAG_ADC_0:
		if (countSamplingTemp0 < 10)
		{
			countSamplingTemp0++;
			temp_0_Sampling += Result;
			Adc_Permission = 0;
		}
		else if(countSamplingTemp0 == 10)
		{
			temp_0 = temp_0_Sampling;
			countSamplingTemp0 = 0;
			temp_0_Sampling = 0;
			Adc_Permission = 0;
		}
		break;
		
		case FLAG_ADC_1:
		if (countSamplingTemp1 < 10)
		{
			countSamplingTemp1++;
			temp_1_Sampling += Result;
			Adc_Permission = 0;
		}
		else if(countSamplingTemp1 == 10)
		{
			temp_1 = temp_1_Sampling;
			countSamplingTemp1 = 0;
			temp_1_Sampling = 0;
			Adc_Permission = 0;
		}
		break;
		
		case FLAG_ADC_2:
		if (countSamplingTemp2 < 10)
		{
			countSamplingTemp2++;
			temp_2_Sampling += Result;
			Adc_Permission = 0;
		}
		else if(countSamplingTemp2 == 10)
		{
			temp_2 = temp_2_Sampling;
			countSamplingTemp2 = 0;
			temp_2_Sampling = 0;
			Adc_Permission = 0;
		}
		break;
		
	}
	AdcControlStatusRegister &= ~(1<<Turning);
}

void adc_handler()
{
	if(get_Systick() > adc_timer_handler)
	{
		switch(Adc_Status)
		{
			case FLAG_ADC_0:
			if(Adc_Permission == 0)
			{
				Read_Adc(1);
			}
			break;
			
			case FLAG_ADC_1:
			if(Adc_Permission == 0)
			{
				Read_Adc(2);
			}
			break;
			
			case FLAG_ADC_FREE:
			case FLAG_ADC_2:
			if(Adc_Permission == 0)
			{
				Read_Adc(0);
			}
			break;
		}
			adc_timer_handler = get_Systick() + 100;
	}

}
//++++++++++++++++++++++temp geter methods ====================
uint8_t get_temp_0()
{
	if (temp_0  == 0)
	{
	return 0;
	} 
	else
	{
	temp_0_0 =0;	
	temp_0_0  = temp_0/10 ;
	temp_0_0 = temp_0_0 * 0.004887;
	temp_0_0 =((50000) / temp_0_0) - 10000;
	temp_0_0 = log(temp_0_0);
	temp_0_0 = 1 / (0.0008857638952 + (0.0002514208257  * temp_0_0) + (0.0000001952872394 * temp_0_0 * temp_0_0 * temp_0_0));
	//Convert in Celsius
	temp_0_0 = temp_0_0 - 273.15;
	return (uint8_t)temp_0_0;
	}
}
uint8_t get_temp_1()
{	
	if (temp_1  == 0)
	{
	return 0;
	} 
	else
	{
	temp_1_1 =0;	
	temp_1_1  = temp_1 /10;
	temp_1_1 = temp_1_1 * 0.004887;
	temp_1_1 =((50000) / temp_1_1) - 10000;
	temp_1_1 = log(temp_1_1);
	temp_1_1 = 1 / (0.0008857638952 + (0.0002514208257 * temp_1_1) + (0.0000001952872394 * temp_1_1 * temp_1_1 * temp_1_1));
	//Convert in Celsius
	temp_1_1 = temp_1_1 - 273.15;
	return  (uint8_t)temp_1_1;
	}
}
uint8_t get_temp_2()
{
	if (temp_2  == 0)
	{
		return 0;
	}
	else
	{
	temp_2_2 = 0;
	temp_2_2  = temp_2 /10;	
	temp_2_2 = temp_2_2 * 0.004887;
	temp_2_2 =((50000) / temp_2_2) - 10000;
	temp_2_2 = log(temp_2_2);
	temp_2_2 = 1 / (0.0008857638952 + (0.0002514208257 * temp_2_2) + (0.0000001952872394 * temp_2_2 * temp_2_2 * temp_2_2));
	//Convert in Celsius
	temp_2_2 = temp_2_2 - 273.15;
	return (uint8_t)temp_2_2;
	}
}