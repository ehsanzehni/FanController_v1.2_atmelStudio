/*
 * Pid_motorh.h
 *
 * Created: 2/19/2022 8:17:20 PM
 *  Author: Gosh
 */ 


#ifndef PID_MOTORH_H_
#define PID_MOTORH_H_

#include <avr/io.h>
/*
#define Tccr_A_timer1  TCCR1A
#define Tccr_B_timer1  TCCR1B
#define Tcnt_timer1  TCNT1
#define Ocie_timer1  OCIE1A
#define Ocr_H_timer1 OCR1AH
#define Ocr_L_timer1 OCR1AL
#define timer1_ISR TIMER1_COMPA_vect
*/
#define Tccr0_timer0  TCCR0
#define timer0_ISR TIMER0_OVF_vect
#define timer0_enable_inttrupt_bit TOIE0
#define inttrupt_register TIMSK

#define Ddr_triac DDRC
#define Port_triac PORTC
#define triac_position 4

void Init_Pid_Motor();
void Run_Sw_Timer();
void Set_FanSpeed(uint8_t FanSpeed);
void Set_FanPermission(uint8_t Permission);

#endif /* PID_MOTORH_H_ */