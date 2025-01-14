/*
 * Smart_House_Slave.c
 *
 * Created: 14/01/2025 01:35:52
 *  Author: pc
 */ 

#include "EEPROM.h"
#include "ADC_Driver.h"
#include "Led.h"
#define F_CPU 8000000LU
#include "SPI_Driver.h"
#include "DC_Motor_Driver.h"
#include "util/delay.h"
#include "Slave_Commands.h"
#include "avr/interrupt.h"
#include "Timer1_driver.h"
unsigned char Command=DUMMY,Room_1_status,Room_2_status;
unsigned char Room_3_status,Room_4_status,TV_status;
volatile unsigned short Input_Volt=0;
volatile unsigned char Actual_Temp=DUMMY,Desired_Temp=DUMMY,Turn_on_flag=0;
int main(void)
{
	Led_vInit('d',0);
	Led_vInit('d',1);
	Led_vInit('d',2);
	Led_vInit('d',3);
	Led_vInit('d',4);
	ADC_vInit();
	DC_Motor_vInit();
	SPI_Slave_vInit();
	Desired_Temp=EEPROM_uRead(ADDRESS_DESIRED_TEMP);
	Turn_on_flag=EEPROM_uRead(ADDRESS_TURN_ON_AC_LAST);
	Room_1_status=EEPROM_uRead(ADDRESS_ROOMS);
	Room_2_status=EEPROM_uRead(ADDRESS_ROOMS+1);
	Room_3_status=EEPROM_uRead(ADDRESS_ROOMS+2);
	Room_4_status=EEPROM_uRead(ADDRESS_ROOMS+3);
	TV_status=EEPROM_uRead(ADDRESS_TV_TURN_ON_LAST);
	if (Room_1_status==1)
	Led_vTurnON('D',0);
	if (Room_2_status==1)
	Led_vTurnON('D',1);
	if (Room_3_status==1)
	Led_vTurnON('D',2);
	if (Room_4_status==1)
	Led_vTurnON('D',3);
	if (TV_status==1)
	Led_vTurnON('D',4);
	Timer1_CTC_OCR1A();
    while(1)
    {
		Command=SPI_Slave_uRecieve(DUMMY);
		switch (Command)
		{
			case ROOM_ONE_STATUS:
			SPI_Slave_uRecieve(Led_uRead('d',0));
			break;
			case ROOM_ONE_LIGHT_TURN_ON:
			Led_vTurnON('D',0);
			EEPROM_vWrite(ADDRESS_ROOMS,Led_uRead('d',0));
			break;
			case ROOM_ONE_LIGHT_TURN_OFF:
			Led_vTurnOFF('d',0);
			EEPROM_vWrite(ADDRESS_ROOMS,Led_uRead('d',0));
			break;
			case ROOM_TWO_STATUS:
			SPI_Slave_uRecieve(Led_uRead('d',1));
			break;
			case ROOM_TWO_LIGHT_TURN_ON:
			Led_vTurnON('D',1);
			EEPROM_vWrite(ADDRESS_ROOMS+1,Led_uRead('d',1));
			break;
			case ROOM_TWO_LIGHT_TURN_OFF:
			Led_vTurnOFF('d',1);
			EEPROM_vWrite(ADDRESS_ROOMS+1,Led_uRead('d',1));
			break;
			case ROOM_THREE_STATUS:
			SPI_Slave_uRecieve(Led_uRead('d',2));
			break;
			case ROOM_THREE_LIGHT_TURN_ON:
			Led_vTurnON('D',2);
			EEPROM_vWrite(ADDRESS_ROOMS+2,Led_uRead('d',2));
			break;
			case ROOM_THREE_LIGHT_TURN_OFF:
			Led_vTurnOFF('d',2);
			EEPROM_vWrite(ADDRESS_ROOMS+2,Led_uRead('d',2));
			break;
			case ROOM_FOUR_STATUS:
			SPI_Slave_uRecieve(Led_uRead('d',3));
			break;
			case ROOM_FOUR_LIGHT_TURN_ON:
			Led_vTurnON('D',3);
			EEPROM_vWrite(ADDRESS_ROOMS+3,Led_uRead('d',3));
			break;
			case ROOM_FOUR_LIGHT_TURN_OFF:
			Led_vTurnOFF('d',3);
			EEPROM_vWrite(ADDRESS_ROOMS+3,Led_uRead('d',3));
			break;
			case TV_STATUS:
			SPI_Slave_uRecieve(Led_uRead('d',4));
			break;
			case TV_TURN_ON:
			Led_vTurnON('D',4);
			EEPROM_vWrite(ADDRESS_TV_TURN_ON_LAST,Led_uRead('d',4));
			break;
			case TV_TURN_OFF:
			Led_vTurnOFF('d',4);
			EEPROM_vWrite(ADDRESS_TV_TURN_ON_LAST,Led_uRead('d',4));
			break;
			case AC_STATUS:
			SPI_Slave_uRecieve(Turn_on_flag);
			break;
			case AC_TURN_ON:
			Turn_on_flag=1;
			EEPROM_vWrite(ADDRESS_TURN_ON_AC_LAST,Turn_on_flag);
			break;
			case AC_TURN_OFF:
			Turn_on_flag=0;
			EEPROM_vWrite(ADDRESS_TURN_ON_AC_LAST,Turn_on_flag);
			break;
			case AC_TEMP_CONTROL:
			Desired_Temp=SPI_Slave_uRecieve(DUMMY);
			EEPROM_vWrite(ADDRESS_DESIRED_TEMP,Desired_Temp);
			break;	
		}		
    }
}

ISR(TIMER1_COMPA_vect)
{
	Input_Volt=(double)((2.56*1000)/1024)*ADC_uRead();
	Actual_Temp=Input_Volt/10;
	if(Actual_Temp>Desired_Temp && Turn_on_flag==1)
	{
		DC_Motor_AC_vTurn_on_Anticlockwise();
		DC_Motor_AC_vSpeed_control(100);
	}
	else
	{
		DC_Motor_AC_vTurn_off();
	}
}