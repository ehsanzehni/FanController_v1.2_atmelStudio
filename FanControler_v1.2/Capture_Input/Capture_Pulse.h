/*
 * Capture_Pulse.h
 *
 * Created: 3/5/2023 1:03:30 AM
 *  Author: ehsan
 */ 


#ifndef CAPTURE_PULSE_H_
#define CAPTURE_PULSE_H_

#define tccr1A_timer1 TCCR1A
#define tccr1B_timer1 TCCR1B
#define step_1 1
#define step_2 2
#define step_3 3
#define CAPTURE_ISR TIMER1_CAPT_vect

void Capture_Pulde_Init();
void Loop_Capture();
uint8_t get_dutyCycle();




#endif /* CAPTURE_PULSE_H_ */