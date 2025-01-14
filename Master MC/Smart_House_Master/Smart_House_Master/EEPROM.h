/*
 * EEPROM.h
 *
 * Created: 08/12/2024 20:58:39
 *  Author: zezom
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_
void EEPROM_vWrite (unsigned short Address, unsigned char data);
unsigned char EEPROM_uRead (unsigned short Address);
#endif /* EEPROM_H_ */