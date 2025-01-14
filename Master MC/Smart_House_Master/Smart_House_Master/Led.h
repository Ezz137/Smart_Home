/*
 * Led.h
 *
 * Created: 02/12/2024 12:51:31
 *  Author: zezom
 */ 


#ifndef LED_H_
#define LED_H_
void Led_vInit(volatile unsigned char PORT,volatile unsigned char pin);
void Led_vTurnON(volatile unsigned char PORT,volatile unsigned char pin);
void Led_vTurnOFF(volatile unsigned char PORT,volatile unsigned char pin);
void Led_vTog(volatile unsigned char PORT,volatile unsigned char pin);
unsigned char Led_uRead(volatile unsigned char PORT,volatile unsigned char pin);
#endif /* LED_H_ */