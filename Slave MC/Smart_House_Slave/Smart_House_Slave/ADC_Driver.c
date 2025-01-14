/*
 * ADC_Driver.c
 *
 * Created: 21/12/2024 01:26:26
 *  Author: zezom
 */ 
#include "Std_macros.h"
#include "avr/io.h"

void ADC_vInit (void)
{
	//REFS1 & REFS0 ALL ZEROES MEANS VREF WILL BE VOLTAGE APPLIED ON VREF PIN
	SET_BIT(ADMUX,REFS0);//same value of AVCC WITH CAPACITOR ON VREF PIN
	SET_BIT(ADMUX,REFS1);//BOTH ONES ON REFS0 AND REFS1 WILL Activate internal voltage 2.56 volt with putting cap. on vref pin
	SET_BIT(ADCSRA,ADEN);//ENABLE ADC OF MICROCONTROLLER
	SET_BIT(ADCSRA,ADPS2);//CLOCK CYCLE 
	SET_BIT(ADCSRA,ADPS1);//CLOCK CYCLE
	//SET_BIT(ADMUX,MUX4);//Differs between ADC0 AND ADC1
}

unsigned short ADC_uRead (void)
{
	unsigned short Return_Valu=0;
	SET_BIT(ADCSRA,ADSC);
	while(READ_BIT(ADCSRA,ADIF)==0);
	SET_BIT(ADCSRA,ADIF);
	Return_Valu=(unsigned short)ADCL;
	Return_Valu|=((unsigned short)ADCH<<8);
	return Return_Valu;
}