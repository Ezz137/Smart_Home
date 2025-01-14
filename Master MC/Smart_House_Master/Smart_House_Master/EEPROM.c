/*
 * EEPROM.c
 *
 * Created: 08/12/2024 20:58:23
 *  Author: zezom
 */ 

#include "avr/io.h"
#include "avr/interrupt.h"
#include "Std_macros.h"
void EEPROM_vWrite (unsigned short Address, unsigned char data)
{
	EEARL=(unsigned char)Address;
	EEARH=(unsigned char)(Address>>8);
	EEDR=data;
	cli();
	SET_BIT(EECR,EEMWE); //After 4 clock cycle will return back to 0
	SET_BIT(EECR,EEWE);
	sei(); 
	//After the end of writing in EEPROM will be back to 0 and next instruction will be executed after 2 Clock cycle
	while(READ_BIT(EECR,EEWE)==1);
}

unsigned char EEPROM_uRead (unsigned short Address)
{
	EEARL=(unsigned char)Address;
	EEARH=(unsigned char)(Address>>8);
	SET_BIT(EECR,EERE);
	return EEDR;
}