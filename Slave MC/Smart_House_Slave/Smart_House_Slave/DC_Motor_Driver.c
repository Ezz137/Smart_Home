/*
 * DC_Motor_Driver.c
 *
 * Created: 05/01/2025 00:53:22
 *  Author: zezom
 */ 


#include "DIO.h"
#define F_CPU 1000000LU
#include "Timer0_driver.h"
//#include "Timer2_Driver.h"
#include "DC_Motor_Driver.h"
#define MOTOR_PORT 'C'
#define AC_PIN 0
//#define HEATER_PIN 2

void DC_Motor_vInit (void)
{
	DIO_vSet_pin(MOTOR_PORT,AC_PIN,1);
	DIO_vSet_pin(MOTOR_PORT,AC_PIN+1,1);
	//DIO_vSet_pin(MOTOR_PORT,HEATER_PIN,1);
	//DIO_vSet_pin(MOTOR_PORT,HEATER_PIN+1,1);
	Timer0_v_FastPWM();
	//Timer2_v_FastPWM();
}

void DC_Motor_AC_vSpeed_control (unsigned char duty_cycle)
{
	Timer0_v_FastPWM_duty_cycle(duty_cycle);
}

/*void DC_Motor_Heater_vSpeed_control (unsigned char duty_cycle)
{
	Timer2_v_FastPWM_Duty_cycle(duty_cycle);
}*/

void DC_Motor_AC_vTurn_on_Anticlockwise (void)
{
	DIO_vWrite_pin(MOTOR_PORT,AC_PIN,1);
	DIO_vWrite_pin(MOTOR_PORT,AC_PIN+1,0);
}

/*void DC_Motor_Heater_vTurn_on_Anticlockwise (void)
{
	DIO_vWrite_pin(MOTOR_PORT,HEATER_PIN,1);
	DIO_vWrite_pin(MOTOR_PORT,HEATER_PIN+1,0);
}*/

void DC_Motor_AC_vTurn_off (void)
{
	DIO_vWrite_pin(MOTOR_PORT,AC_PIN,0);
	DIO_vWrite_pin(MOTOR_PORT,AC_PIN+1,0);
	DC_Motor_AC_vSpeed_control(0);
}

/*void DC_Motor_Heater_vTurn_off (void)
{
	DIO_vWrite_pin(MOTOR_PORT,HEATER_PIN,0);
	DIO_vWrite_pin(MOTOR_PORT,HEATER_PIN+1,0);
	DC_Motor_Heater_vSpeed_control(0);
}*/
/*void DC_Motor_AC_vTurn_on_clockwise (void)
{
	DIO_vWrite_pin(MOTOR_PORT,AC_PIN,0);
	DIO_vWrite_pin(MOTOR_PORT,AC_PIN+1,1);
}

void DC_Motor_Heater_vTurn_on_clockwise (void)
{
	DIO_vWrite_pin(MOTOR_PORT,HEATER_PIN,0);
	DIO_vWrite_pin(MOTOR_PORT,HEATER_PIN+1,1);
}*/

