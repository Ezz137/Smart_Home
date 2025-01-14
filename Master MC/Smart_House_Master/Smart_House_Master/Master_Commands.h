/*
 * Master_Commands.h
 *
 * Created: 13/01/2025 17:28:43
 *  Author: pc
 */ 


#ifndef MASTER_COMMANDS_H_
#define MASTER_COMMANDS_H_
#define EEPROM_ADMIN_PASS_STATUS_ADDRESS 0X20
#define EEPROM_ADMIN_PASS_FIRST_ADDRESS 0X21 
#define EEPROM_GUSET_PASS_STATUS_ADDRESS 0X25
#define EEPROM_GUEST_PASS_FIRST_ADDRESS 0X26 
#define EEPROM_BLOCK_PASS_STATUS_ADDRESS 0X30
#define EEPROM_BLOCK_PASS_COUNTER_ADDRESS 0X31
#define DELAY_TIME_BEFORE_CLEAR_SCREEN_MILLI_SEC 1000
#define COUNTER_TIMER_0_TIME_OUT_ADMIN 500
#define COUNTER_TIMER_2_TIME_OUT_GUEST 250
#define KEYPAD_ENTRY_DELAY 250
#define NUMBER_OF_TRIES 3
#define BLOCK_TIME 35
#define DELAY_FOR_SEND_TO_SLAVE_SPI 250
#include "Led.h"
#include "Keypad.h"
#include "LCD.h"
#include "SPI_Driver.h"
#include "EEPROM.h"
#define F_CPU 8000000LU
#include "util/delay.h"
#include "Slave_Commands.h"
#include "avr/interrupt.h"
#include "Smart_home_funcs.h"
#endif /* MASTER_COMMANDS_H_ */