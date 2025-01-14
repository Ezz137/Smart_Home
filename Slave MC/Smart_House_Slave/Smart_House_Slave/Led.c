/*
 * Led.c
 *
 * Created: 02/12/2024 12:51:20
 *  Author: zezom
 */ 
#include "DIO.h"


void Led_vInit(volatile unsigned char PORT,volatile unsigned char pin)
{
	DIO_vSet_pin(PORT,pin,1);
}

void Led_vTurnON(volatile unsigned char PORT,volatile unsigned char pin)
{
	DIO_vWrite_pin(PORT,pin,1);
}

void Led_vTurnOFF(volatile unsigned char PORT,volatile unsigned char pin)
{
	DIO_vWrite_pin(PORT,pin,0);
}

void Led_vTog(volatile unsigned char PORT,volatile unsigned char pin)
{
	DIO_vTog_pin(PORT,pin);
}

unsigned char Led_uRead(volatile unsigned char PORT,volatile unsigned char pin)
{
	 return DIO_uRead_pin(PORT,pin);
}