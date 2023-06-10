/*
 * Relays.h
 *
 * Created: 2/20/2022 9:19:58 PM
 *  Author: Gosh
 */ 


#ifndef RELAYS_H_
#define RELAYS_H_


#define Ddr_Relay_1 DDRC


#define Port_Relay_1 PORTC


#define Relay_1_Position 3





void Relay_1_Target(uint8_t mode);
void Relays_Init();

#endif /* RELAYS_H_ */