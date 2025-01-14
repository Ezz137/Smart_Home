/*
 * Timer0_driver.c
 *
 * Created: 24/12/2024 14:20:21
 *  Author: zezom
 */ 

#include "avr/interrupt.h"
#include "Std_macros.h"
#include "avr/io.h"

void Timer0_CTC_vInit(void)
{
	SET_BIT(TCCR0,CS02);
	SET_BIT(TCCR0,CS00);//SET CLOCK CYCLE WITH PRESCALER 1024
	SET_BIT(TCCR0,WGM01);//SET TIMER MODE WITH CTC CLEAR TIME REGISTER (TCNT0) WITH COMPARE MATCH
	OCR0=78;
	sei();
	SET_BIT(TIMSK,OCIE0);//SET ENABLE INTERUPT OF CTC CLEAR TIME REGISTER (TCNT0) WITH COMPARE MATCH
}

void Timer0_waveform_non_PWM_vInit(void)
{
	SET_BIT(DDRB,3);//to set OC0 as Output
	SET_BIT(TCCR0,CS02);
	SET_BIT(TCCR0,CS00);//SET CLOCK CYCLE WITH PRESCALER 1024  frq=freq of mc/(2*(1+ocr0)*prescaler
	OCR0=69;
	SET_BIT(TCCR0,WGM01);//SET TIMER MODE WITH CTC CLEAR TIME REGISTER (TCNT0) WITH COMPARE MATCH
	SET_BIT(TCCR0,COM00);//SET OC0 BY TOGGLE 
}

void Timer0_v_FastPWM(void)
{
	SET_BIT(DDRB,3);//to set OC0 as Output
	SET_BIT(TCCR0,CS02);
	SET_BIT(TCCR0,CS00);//SET CLOCK CYCLE WITH PRESCALER 1024  frq=freq of mc/(2*(1+ocr0)*prescaler
	//OCR0=64;
	SET_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);//SET TIMER MODE WITH FAST PWM
	SET_BIT(TCCR0,COM01);//10 means non inverting mode clear on OCR0 set on overflow 
	//SET_BIT(TCCR0,COM00);//11 means inverting mode set on OCR0 and clear on overflow
}

void Timer0_v_Phase_Control_PWM(void)
{
	SET_BIT(DDRB,3);//to set OC0 as Output
	SET_BIT(TCCR0,CS02);
	SET_BIT(TCCR0,CS00);//SET CLOCK CYCLE WITH PRESCALER 1024  frq=freq of mc/(2*(1+ocr0)*prescaler
	OCR0=64;
	SET_BIT(TCCR0,WGM00);//SET TIMER MODE WITH phase control PWM
	SET_BIT(TCCR0,COM01);//10 means from OCR0 to 0 to OCR0 on mode
	SET_BIT(TCCR0,COM00);//11 means from OCR0 to 255 to OCR0 on mode
	
}

void Timer0_v_FastPWM_duty_cycle(unsigned char duty_cycle)
{
	OCR0=((unsigned long)duty_cycle*255/100);
}