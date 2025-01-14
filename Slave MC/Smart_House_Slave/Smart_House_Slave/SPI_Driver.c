/*
 * SPI_Driver.c
 *
 * Created: 07/01/2025 18:32:07
 *  Author: pc
 */ 
#include "DIO.h"
#include "Std_macros.h"
#define F_CPU 8000000LU
#include "util/delay.h"
#include "avr/interrupt.h"
#include "avr/io.h"
#include "SPI_Driver.h"

void SPI_Master_vInit (void)
{
	//SET PINS OF MOSI AND MISO AND SCK AND SS AS OUTPUT PINS AND INPUT PINS
	DIO_vSet_pin('B',4,1);
	DIO_vSet_pin('B',5,1);
	DIO_vSet_pin('B',6,0);
	DIO_vSet_pin('B',7,1);
	//SET THIS MC AS MASTER
	SET_BIT(SPCR,MSTR);
	//SET Frequency of SPI clock of master controller by /16
	SET_BIT(SPCR,SPR0);
	//ENABLE SPI MODE
	SET_BIT(SPCR,SPE);
	/*enable interrupt
	sei();
	SET_BIT(SPCR,SPIE);*/
	//SET SS PIN AS ACTIVE HIGH
	DIO_vWrite_pin('B',4,1);
}

void SPI_Slave_vInit (void)
{
	//SET PINS OF MOSI AND MISO AND SCK AND SS AS OUTPUT PINS AND INPUT PINS
	DIO_vSet_pin('B',4,0);
	DIO_vSet_pin('B',5,0);
	DIO_vSet_pin('B',6,1);
	DIO_vSet_pin('B',7,0);
	//ENABLE SPI MODE
	SET_BIT(SPCR,SPE);
	/*//enable interrupt
	sei();
	SET_BIT(SPCR,SPIE);*/
}

unsigned char SPI_Master_uTransmit (unsigned char Data)
{
	//set ss pin as active low 
	DIO_vWrite_pin('B',4,0);
	//write data in data register of SPI
	SPDR=Data;
	//ensure that flag is one this line need to be cancelled while using interrupt
	while (READ_BIT(SPSR,SPIF)==0);
	//RETURN DATA OF DATA REGISTER AFTER DATA EXCHANGE
	return SPDR;
}

unsigned char SPI_Slave_uRecieve (unsigned char Data)
{
	//write data in data register of SPI
	SPDR=Data;
	//ensure that flag is one this line need to be cancelled while using interrupt
	while (READ_BIT(SPSR,SPIF)==0);
	//RETURN DATA OF DATA REGISTER AFTER DATA EXCHANGE
	return SPDR;
}

void SPT_Master_vSend_String (const char *Data)
{
	while(*Data!=0)
	{
		SPI_Master_uTransmit(*Data);
		_delay_ms(300);
		Data++;
	}
}