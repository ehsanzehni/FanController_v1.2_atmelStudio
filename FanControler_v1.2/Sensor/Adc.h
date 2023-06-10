/*
 * Adc.h
 *
 * Created: 1/21/2023 1:02:25 AM
 *  Author: ehsan
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

#define StartConversion ADSC

#define Result ADC
#define Turning ADEN
#define AdcControlStatusRegister ADCSRA
#define AdcMultiplexerSelectionRegister ADMUX
#define Adc_ISR ADC_vect

#define FLAG_ADC_0 1
#define FLAG_ADC_1 2
#define FLAG_ADC_2 3
#define FLAG_ADC_FREE 0

uint8_t Adc_Status;
uint8_t Adc_Permission;

void Adc_Init();
void adc_handler();
uint8_t get_temp_0();
uint8_t get_temp_1();
uint8_t get_temp_2();





#endif /* ADC_H_ */