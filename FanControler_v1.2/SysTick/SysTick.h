/*
 * SysTick.h
 *
 * Created: 1/25/2022 2:23:15 AM
 *  Author: Gosh
 */ 
#include <avr/io.h>

#ifndef SYSTICK_H_
#define SYSTICK_H_



#define Tccr_timer2  TCCR2
#define OCR_timer2  OCR2
#define Ocie_timer2  OCIE2
#define timer2_ISR TIMER2_COMP_vect


void SysTick_Init();
uint32_t get_Systick();



#endif /* SYSTICK_H_ */