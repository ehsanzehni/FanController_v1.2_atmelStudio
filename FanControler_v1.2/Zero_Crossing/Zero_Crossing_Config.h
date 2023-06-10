/*
 * zero_config.h
 *
 * Created: 2/15/2022 6:23:26 PM
 *  Author: Gosh
 */ 


#ifndef ZERO_CONFIG_H_
#define ZERO_CONFIG_H_

#define zero_DDR DDRD
#define zero_PORT PORTD
#define zero_PIN PIND

#define Z_Position 2


#define Interrupt_Zero_Mode 1
#define PullUp_Zero_Mode 0



#define Enable_Interrupt_Zero GICR
#define EXT_INT_STATUS_REGISTER_Zero  MCUCR
#define int_Mode_Zero INT0
#define isr_mode_Zero INT0_vect



#endif /* ZERO_CONFIG_H_ */