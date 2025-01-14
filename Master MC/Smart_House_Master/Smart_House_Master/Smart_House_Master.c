#include "Master_Commands.h"
volatile unsigned char counter_block_timeout=0;
unsigned char keypad_entry=DUMMY,status_admin=DUMMY,status_guest=DUMMY,status_block=DUMMY;
unsigned char PASS[4];
unsigned char iteration=0,tries=NUMBER_OF_TRIES,obj_status,AC_TEMP;
int main(void)
{
	status_block=EEPROM_uRead(EEPROM_BLOCK_PASS_STATUS_ADDRESS);
	status_admin=EEPROM_uRead(EEPROM_ADMIN_PASS_STATUS_ADDRESS);
	status_guest=EEPROM_uRead(EEPROM_GUSET_PASS_STATUS_ADDRESS);
	LCD_vInit();
	Keypad_vInit();
	Led_vInit('c',0);
	Led_vInit('c',1);
	Led_vInit('c',2);
	SPI_Master_vInit();
	LCD_vSendString("Welcome");
	LCD_vMoveCursor(2,1);
	LCD_vSendString("SMART HOME");
	_delay_ms(DELAY_TIME_BEFORE_CLEAR_SCREEN_MILLI_SEC);
	LCD_vClrscreen();
    while(1)
    {
		if (status_block!=DUMMY)
		{//ENSURE BLOCK TIME FULLY FINISHED
			Led_vTurnON('c',2);
			LCD_vSendString("you are blocked");
			counter_block_timeout=EEPROM_uRead(EEPROM_BLOCK_PASS_COUNTER_ADDRESS);
			LCD_vMoveCursor(2,1);
			LCD_vSendChar((counter_block_timeout-48)/10);
			LCD_vSendChar((counter_block_timeout-48)%10);
			LCD_vSendString(" seconds");
			for (;counter_block_timeout<BLOCK_TIME;counter_block_timeout++)
			{
				EEPROM_vWrite(EEPROM_BLOCK_PASS_COUNTER_ADDRESS,counter_block_timeout);
				_delay_ms(1000);
			}
			tries=NUMBER_OF_TRIES;
			EEPROM_vWrite(EEPROM_BLOCK_PASS_STATUS_ADDRESS,0xff);
			status_block=EEPROM_uRead(EEPROM_BLOCK_PASS_STATUS_ADDRESS);
			_delay_ms(DELAY_TIME_BEFORE_CLEAR_SCREEN_MILLI_SEC);
			LCD_vClrscreen();
			Led_vTurnOFF('c',2);
		}
		LCD_vClrscreen();
		LCD_vSendString("select the acc");
		LCD_vMoveCursor(2,1);
		LCD_vSendString("1-Admin 2-guest");
		Led_vTurnOFF('c',0);
		Led_vTurnOFF('c',1);
		_delay_ms(DELAY_TIME_BEFORE_CLEAR_SCREEN_MILLI_SEC);
		while((keypad_entry=Keypad_uRead())==DUMMY);
		//ENTERING ADMIN PROFILE
        if (keypad_entry=='1')
        {
			if (status_admin==DUMMY)
			{
				_delay_ms(DELAY_TIME_BEFORE_CLEAR_SCREEN_MILLI_SEC);
				LCD_vClrscreen();
				LCD_vSendString("PAS FIRST TIME");
				LCD_vMoveCursor(2,1);
				LCD_vSendString("ADMIN PASS:");//11 LETTER
				for (iteration=0;iteration<4;iteration++)
				{
					while((keypad_entry=Keypad_uRead())==DUMMY);
					LCD_vSendChar(keypad_entry);
					_delay_ms(KEYPAD_ENTRY_DELAY);
					EEPROM_vWrite(EEPROM_ADMIN_PASS_FIRST_ADDRESS+iteration,keypad_entry-48);
					LCD_vMoveCursor(2,12+iteration);
					LCD_vSendChar('*');
				}//OK
				EEPROM_vWrite(EEPROM_ADMIN_PASS_STATUS_ADDRESS,0X01);
				_delay_ms(DELAY_TIME_BEFORE_CLEAR_SCREEN_MILLI_SEC);
				LCD_vClrscreen();
			}//OK
			LCD_vClrscreen();
			LCD_vSendString("Admin acc");
			LCD_vMoveCursor(2,1);
			LCD_vSendString("Admin Pass:");//11 letter
			for (iteration=0;iteration<4;iteration++)
			{
				while((keypad_entry=Keypad_uRead())==DUMMY);
				LCD_vSendChar(keypad_entry);
				_delay_ms(KEYPAD_ENTRY_DELAY);
				PASS[iteration]=keypad_entry-48;
				LCD_vMoveCursor(2,12+iteration);
				LCD_vSendChar('*');
			}//OK
			_delay_ms(DELAY_TIME_BEFORE_CLEAR_SCREEN_MILLI_SEC);
			LCD_vClrscreen();
			if (PASS[0]==EEPROM_uRead(EEPROM_ADMIN_PASS_FIRST_ADDRESS) && PASS[1]==EEPROM_uRead(EEPROM_ADMIN_PASS_FIRST_ADDRESS+1) && PASS[2]==EEPROM_uRead(EEPROM_ADMIN_PASS_FIRST_ADDRESS+2)&& PASS[3]==EEPROM_uRead(EEPROM_ADMIN_PASS_FIRST_ADDRESS+3))
			{
				Led_vTurnON('c',0);
				LCD_vSendString("correct pass");
				_delay_ms(DELAY_TIME_BEFORE_CLEAR_SCREEN_MILLI_SEC);
				LCD_vClrscreen();
				Admin_main_menu	();					
			}								
			else
			{
				Wrong_pass();
			}//OK
		}																											
		else if (keypad_entry=='2')
		{
				if (status_guest==DUMMY)
				{
					_delay_ms(DELAY_TIME_BEFORE_CLEAR_SCREEN_MILLI_SEC);
					LCD_vClrscreen();
					LCD_vSendString("PAS FIRST TIME");
					LCD_vMoveCursor(2,1);
					LCD_vSendString("GUEST PASS:");//11 LETTER
					for (iteration=0;iteration<4;iteration++)
					{
						while((keypad_entry=Keypad_uRead())==DUMMY);
						LCD_vSendChar(keypad_entry);
						_delay_ms(KEYPAD_ENTRY_DELAY);
						EEPROM_vWrite(EEPROM_GUEST_PASS_FIRST_ADDRESS+iteration,keypad_entry-48);
						LCD_vMoveCursor(2,12+iteration);
						LCD_vSendChar('*');
					}
					EEPROM_vWrite(EEPROM_GUSET_PASS_STATUS_ADDRESS,0X01);
					_delay_ms(DELAY_TIME_BEFORE_CLEAR_SCREEN_MILLI_SEC);
					LCD_vClrscreen();
				}
				LCD_vClrscreen();
				LCD_vSendString("Guest acc");
				LCD_vMoveCursor(2,1);
				LCD_vSendString("Guest Pass:");//11 letter
				for (iteration=0;iteration<4;iteration++)
				{
					while((keypad_entry=Keypad_uRead())==DUMMY);
					LCD_vSendChar(keypad_entry);
					_delay_ms(KEYPAD_ENTRY_DELAY);
					PASS[iteration]=keypad_entry-48;
					LCD_vMoveCursor(2,12+iteration);
					LCD_vSendChar('*');
				}
				_delay_ms(DELAY_TIME_BEFORE_CLEAR_SCREEN_MILLI_SEC);
				LCD_vClrscreen();
				if (PASS[0]==EEPROM_uRead(EEPROM_GUEST_PASS_FIRST_ADDRESS) && PASS[1]==EEPROM_uRead(EEPROM_GUEST_PASS_FIRST_ADDRESS+1) && PASS[2]==EEPROM_uRead(EEPROM_GUEST_PASS_FIRST_ADDRESS+2)&& PASS[3]==EEPROM_uRead(EEPROM_GUEST_PASS_FIRST_ADDRESS+3))
				{
					Led_vTurnON('c',1);
					LCD_vSendString("correct pass");
					_delay_ms(DELAY_TIME_BEFORE_CLEAR_SCREEN_MILLI_SEC);
					LCD_vClrscreen();
					Guest_main_menu();
				}
				else
				{
					Wrong_pass();
				}
		}			
		else
		{//start of else i you enter any unselected key 
			LCD_vClrscreen();
			LCD_vSendString("wrong input");
			_delay_ms(DELAY_TIME_BEFORE_CLEAR_SCREEN_MILLI_SEC);
		}//end of else i you enter any unselected key		
    }//end of while 1	
}//end of int main