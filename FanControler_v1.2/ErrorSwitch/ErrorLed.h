/*
 * ErrorLed.h
 *
 * Created: 4/26/2023 1:03:00 PM
 *  Author: ehsan
 */ 


#ifndef ERRORLED_H_
#define ERRORLED_H_

#define Error_Led_DDR DDRD
#define Error_Led_PORT PORTD

#define Error_Led_Posion 4


void Error_Handler();
void init_Error_Led();

#endif /* ERRORLED_H_ */