/*
 * EEPROM.h
 *
 * Created: 8/12/2022 8:50:48 PM
 *  Author: Mohamed Elsayed
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_
#include "STD_MACROS.h"

uint8_t EEPROM_read(uint16_t);
void EEPROM_write(uint16_t location,uint8_t data);




#endif /* EEPROM_H_ */