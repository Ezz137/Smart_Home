/*
 * SPI_Driver.h
 *
 * Created: 07/01/2025 18:32:26
 *  Author: pc
 */ 


#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_
void SPI_Master_vInit (void);
void SPI_Slave_vInit (void);
unsigned char SPI_Master_uTransmit (unsigned char Data);
unsigned char SPI_Slave_uRecieve (unsigned char Data);
void SPT_Master_vSend_String (const char *Data);
#endif /* SPI_DRIVER_H_ */