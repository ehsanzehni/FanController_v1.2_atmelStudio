/*
 * ErrorSwitch.h
 *
 * Created: 4/25/2023 9:29:43 PM
 *  Author: ehsan
 */ 


#ifndef ERRORSWITCH_H_
#define ERRORSWITCH_H_

#define switch_DDR DDRD
#define switch_PORT PORTD
#define switch_PIN PIND

#define switch_Position 3

#define Enable_Interrupt_SWITCH GICR
#define EXT_INT_STATUS_REGISTER_SWITCH  MCUCR
#define int_Mode_Switch INT1
#define isr_mode_Switch INT1_vect

void Error_Switch_Init();



#endif /* ERRORSWITCH_H_ */