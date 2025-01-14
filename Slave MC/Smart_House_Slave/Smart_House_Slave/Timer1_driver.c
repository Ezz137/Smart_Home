/*
 * Timer1_driver.c
 *
 * Created: 31/12/2024 23:25:24
 *  Author: zezom
 */ 
#include "avr/io.h"
#include "Std_macros.h"
#include "avr/interrupt.h"

void Timer1_CTC_OCR1A (void)
{
	SET_BIT(TCCR1B,CS12);
	SET_BIT(TCCR1B,CS10);//TO SET PRE SCALER BY 1024
	SET_BIT(TCCR1B,WGM12);//TO SET CTC OCR1A
	OCR1A=700;
	SET_BIT(TIMSK,OCIE1A);
	sei();
}

void Timer1_FAST_PWM_ICR (double degree)
{
	double value;
	value=(double)1+0.0055556*degree;
	if (value<=1)
	{
		value=1;
	}
	else if (value>=2)
	{
		value=2;
	}
	else
	{
		value=value;
	}
	SET_BIT(DDRD,5); //SET OC1A AS OUTPUT PIN
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13); //SET MODE FAST PWM ICR1
	SET_BIT(TCCR1B,CS10); //SET PRESCALER BY 1S
	SET_BIT(TCCR1A,COM1A1);//SET OC1A NON INVERTING MODE
	ICR1=19999;
	OCR1A=value*1000;
}