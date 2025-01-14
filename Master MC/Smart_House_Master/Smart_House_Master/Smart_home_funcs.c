/*
 * Smart_home_funcs.c
 *
 * Created: 14/01/2025 12:59:53
 *  Author: pc
 */ 

#include "Master_Commands.h"
extern volatile unsigned char counter_block_timeout;
extern unsigned char keypad_entry,status_admin,status_guest,status_block;
extern unsigned char ADMIN_PASS[4],GUEST_PASS[4];
extern unsigned char iteration,tries,obj_status,AC_TEMP;

void Wrong_pass (void) //when you set your password wrong
{
	LCD_vSendString("wrong pass");
	tries--;
	LCD_vMoveCursor(2,1);
	LCD_vSendString("tries:");
	LCD_vSendChar(tries+'0');
	_delay_ms(DELAY_TIME_BEFORE_CLEAR_SCREEN_MILLI_SEC);
	LCD_vClrscreen();
	if (tries==0)
	{
		Led_vTurnON('c',2);
		EEPROM_vWrite(EEPROM_BLOCK_PASS_STATUS_ADDRESS,0x01);
		LCD_vSendString("you are blocked");
		LCD_vMoveCursor(2,1);
		LCD_vSendChar((BLOCK_TIME/10)+'0');
		LCD_vSendChar((BLOCK_TIME%10)+'0');
		LCD_vSendString(" seconds");
		for (counter_block_timeout=BLOCK_TIME;counter_block_timeout>0;counter_block_timeout--)
		{
			EEPROM_vWrite(EEPROM_BLOCK_PASS_COUNTER_ADDRESS,counter_block_timeout);
			_delay_ms(1000);
		}
		tries=NUMBER_OF_TRIES;
		EEPROM_vWrite(EEPROM_BLOCK_PASS_STATUS_ADDRESS,0xff);
		_delay_ms(DELAY_TIME_BEFORE_CLEAR_SCREEN_MILLI_SEC);
		LCD_vClrscreen();
		Led_vTurnOFF('c',2);
	}
}

void TV_menu (void)
{
	LCD_vClrscreen();
	LCD_vSendString("TV Set:");
	_delay_ms(DELAY_FOR_SEND_TO_SLAVE_SPI);
	SPI_Master_uTransmit(TV_STATUS);
	_delay_ms(DELAY_FOR_SEND_TO_SLAVE_SPI);
	obj_status=SPI_Master_uTransmit(DUMMY);
	if(obj_status==0)
	{
		LCD_vSendString("OFF");
	}
	else
	{
		LCD_vSendString("ON");
	}
	LCD_vMoveCursor(2,1);
	LCD_vSendString("1-ON 2-OFF 3-RET");
	while((keypad_entry=Keypad_uRead())==DUMMY);
	if(keypad_entry=='1')
	{
		SPI_Master_uTransmit(TV_TURN_ON);
		LCD_vClrscreen();
	}
	else if (keypad_entry=='2')
	{
		SPI_Master_uTransmit(TV_TURN_OFF);
		LCD_vClrscreen();
	}
	else if (keypad_entry=='3')
	{
		LCD_vClrscreen();
		Sub_More_Admin_menu();
	}
	else 
	{
		LCD_vClrscreen();
		LCD_vSendString("wrong input");
		_delay_ms(DELAY_TIME_BEFORE_CLEAR_SCREEN_MILLI_SEC);
		TV_menu();
	}	
}

void Room_menu (unsigned char number,unsigned char acc)
{
	LCD_vClrscreen();
	LCD_vSendString("Ro:");
	LCD_vSendChar(number+'0');
	LCD_vSendString(" set:");
	_delay_ms(DELAY_FOR_SEND_TO_SLAVE_SPI);
	switch(number)
	{	
		case 1:
		SPI_Master_uTransmit(ROOM_ONE_STATUS);
		break;
		case 2:
		SPI_Master_uTransmit(ROOM_TWO_STATUS);
		break;
		case 3:
		SPI_Master_uTransmit(ROOM_THREE_STATUS);
		break;
		default:
		SPI_Master_uTransmit(ROOM_FOUR_STATUS);
		break;
	}	
	_delay_ms(DELAY_FOR_SEND_TO_SLAVE_SPI);
	obj_status=SPI_Master_uTransmit(DUMMY);
	if(obj_status==0)
	{
		LCD_vSendString("OFF");
	}
	else
	{
		LCD_vSendString("ON");
	}
	LCD_vMoveCursor(2,1);
	LCD_vSendString("1-ON 2-OFF 3-RET");
	while((keypad_entry=Keypad_uRead())==DUMMY);
	if(keypad_entry=='1')
	{
		switch(number)
		{
			case 1:
			SPI_Master_uTransmit(ROOM_ONE_LIGHT_TURN_ON);
			break;
			case 2:
			SPI_Master_uTransmit(ROOM_TWO_LIGHT_TURN_ON);
			break;
			case 3:
			SPI_Master_uTransmit(ROOM_THREE_LIGHT_TURN_ON);
			break;
			default:
			SPI_Master_uTransmit(ROOM_FOUR_LIGHT_TURN_ON);
			break;
		}
		LCD_vClrscreen();
	}
	else if (keypad_entry=='2')
	{
		switch(number)
		{
			case 1:
			SPI_Master_uTransmit(ROOM_ONE_LIGHT_TURN_OFF);
			break;
			case 2:
			SPI_Master_uTransmit(ROOM_TWO_LIGHT_TURN_OFF);
			break;
			case 3:
			SPI_Master_uTransmit(ROOM_THREE_LIGHT_TURN_OFF);
			break;
			default:
			SPI_Master_uTransmit(ROOM_FOUR_LIGHT_TURN_OFF);
			break;
		}
		LCD_vClrscreen();
	}
	else if (keypad_entry=='3')
	{
		LCD_vClrscreen();
		switch(acc)
		{//go to sub menu according flag indicates guest or admin profile
			case 1:
			switch (number)
			{
				default:
				Admin_main_menu();
				break;
				case 4:
				Sub_More_Admin_menu();
				break;
			}
			break;
			case 2:
			Guest_main_menu();
			break;
		}		
	}
	else 
	{
		LCD_vClrscreen();
		LCD_vSendString("wrong input");
		_delay_ms(DELAY_TIME_BEFORE_CLEAR_SCREEN_MILLI_SEC);
		Room_menu(number,acc);
	}
}

void Guest_main_menu (void)
{
	_delay_ms(DELAY_TIME_BEFORE_CLEAR_SCREEN_MILLI_SEC);
	LCD_vClrscreen();
	LCD_vSendString("1-ROOM1  2-ROOM2");
	LCD_vMoveCursor(2,1);
	LCD_vSendString("3-ROOM3  4-ROOM4");
	while((keypad_entry=Keypad_uRead())==DUMMY);
	_delay_ms(KEYPAD_ENTRY_DELAY);
	if (keypad_entry=='1')
	{
		Room_menu(1,2);
	}
	else if (keypad_entry=='2')
	{
		Room_menu(2,2);
	}
	else if (keypad_entry=='3')
	{
		Room_menu(3,2);
	}
	else if (keypad_entry=='4')
	{
		Room_menu(4,2);
	}
	else
	{
		LCD_vClrscreen();
		LCD_vSendString("wrong input");
		_delay_ms(DELAY_TIME_BEFORE_CLEAR_SCREEN_MILLI_SEC);
		Guest_main_menu();
	}
}

void Admin_main_menu (void)
{
	LCD_vClrscreen();
	LCD_vSendString("1-ROOM1  2-ROOM2");
	LCD_vMoveCursor(2,1);
	LCD_vSendString("3-ROOM3  4-MORE");
	while((keypad_entry=Keypad_uRead())==DUMMY);
	_delay_ms(KEYPAD_ENTRY_DELAY);
	if (keypad_entry=='1')
	{
		Room_menu(1,1);
	}
	else if (keypad_entry=='2')
	{
		Room_menu(2,1);
	}
	else if (keypad_entry=='3')
	{
		Room_menu(3,1);
	}
	else if (keypad_entry=='4')
	{
		Sub_More_Admin_menu();
	}
	else
	{
		LCD_vClrscreen();
		LCD_vSendString("wrong input");
		_delay_ms(DELAY_TIME_BEFORE_CLEAR_SCREEN_MILLI_SEC);
		Admin_main_menu();
		
	}
}

void Sub_More_Admin_menu(void)
{
	LCD_vClrscreen();
	LCD_vSendString("1-ROOM4  2-TV");
	LCD_vMoveCursor(2,1);
	LCD_vSendString("3-AC  4-RET");
	while((keypad_entry=Keypad_uRead())==DUMMY);
	_delay_ms(KEYPAD_ENTRY_DELAY);
	if (keypad_entry=='1')
	{
		Room_menu(4,1);
	}
	else if (keypad_entry=='2')
	{
		TV_menu();
	}
	else if (keypad_entry=='3')
	{
		AC_Menu();
	}
	else if (keypad_entry==4)
	{
		Admin_main_menu();
	}
	else
	{
		LCD_vClrscreen();
		LCD_vSendString("Time out");
		_delay_ms(DELAY_TIME_BEFORE_CLEAR_SCREEN_MILLI_SEC);
		//go to main menu code
	}
}

void AC_Menu (void)
{
	LCD_vClrscreen();
	LCD_vSendString("1-TEMP CONTROL");
	LCD_vMoveCursor(2,1);
	LCD_vSendString("2-ON/OFF 3-RET");
	while((keypad_entry=Keypad_uRead())==DUMMY);
	_delay_ms(KEYPAD_ENTRY_DELAY);
	if (keypad_entry=='2')
	{
		AC_ON_OFF_MENU:LCD_vClrscreen();
		LCD_vSendString("AC Set:");
		_delay_ms(DELAY_FOR_SEND_TO_SLAVE_SPI);
		SPI_Master_uTransmit(AC_STATUS);
		_delay_ms(DELAY_FOR_SEND_TO_SLAVE_SPI);
		obj_status=SPI_Master_uTransmit(DUMMY);
		if(obj_status==0)
		{
			LCD_vSendString("OFF");
		}	
		else
		{
			LCD_vSendString("ON");
		}
		LCD_vMoveCursor(2,1);
		LCD_vSendString("1-ON 2-OFF 3-RET");
		while((keypad_entry=Keypad_uRead())==DUMMY);
		if(keypad_entry=='1')
		{
			SPI_Master_uTransmit(AC_TURN_ON);
			LCD_vClrscreen();
		}
		else if (keypad_entry=='2')
		{
			SPI_Master_uTransmit(AC_TURN_OFF);
			LCD_vClrscreen();
		}
		else if (keypad_entry=='3')
		{
			LCD_vClrscreen();
			AC_Menu();
		}//OK
		else 
		{
			LCD_vClrscreen();
			LCD_vSendString("wrong input");
			_delay_ms(DELAY_TIME_BEFORE_CLEAR_SCREEN_MILLI_SEC);
			goto AC_ON_OFF_MENU;
		}
	}	
	else if (keypad_entry=='1')
	{
		LCD_vClrscreen();
		LCD_vSendString("TEMP:");
		while((keypad_entry=Keypad_uRead())==DUMMY );
		LCD_vSendChar(keypad_entry);
		_delay_ms(DELAY_TIME_BEFORE_CLEAR_SCREEN_MILLI_SEC);
		AC_TEMP=(keypad_entry-48)*10;
		while((keypad_entry=Keypad_uRead())==DUMMY);
		LCD_vSendChar(keypad_entry);
		_delay_ms(DELAY_TIME_BEFORE_CLEAR_SCREEN_MILLI_SEC);
		AC_TEMP=AC_TEMP+(keypad_entry-48);
		LCD_vClrscreen();
		SPI_Master_uTransmit(AC_TEMP_CONTROL);
		_delay_ms(DELAY_FOR_SEND_TO_SLAVE_SPI);
		SPI_Master_uTransmit(AC_TEMP);
	}
	else if (keypad_entry=='3')
	{
		Sub_More_Admin_menu();
	}
	else
	{
		LCD_vClrscreen();
		LCD_vSendString("wrong input");
		_delay_ms(DELAY_TIME_BEFORE_CLEAR_SCREEN_MILLI_SEC);
		AC_Menu();
	}	
			
}