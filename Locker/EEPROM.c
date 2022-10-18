/*
 * EEPROM.c
 * MCal Driver
 * Created: 8/12/2022 8:50:30 PM
 *  Author: Mohamed Elsayed
 */ 
#include "EEPROM.h"
/*****************************************************************************
* Function Name: EEPROM_read
* Purpose      : Read data from EEPROM location
* Parameters   : uint16_t location (as locations from 0 to 1023)
* Return value : uint8_t data (as any location in EEPROM consist of 8 bits) 
*****************************************************************************/
uint8_t EEPROM_read(uint16_t location){
	while(GETBIT(EECR,EEWE)==1){}
	EEAR = location;
	SETBIT(EECR,EERE);
	return EEDR;
}
/*****************************************************************************
* Function Name: EEPROM_write
* Purpose      : store data in EEPROM location
* Parameters   : uint16_t location & uint8_t data
* Return value : void
*****************************************************************************/
void EEPROM_write(uint16_t location,uint8_t data){
	while(GETBIT(EECR,EEWE)==1){}
	EEAR = location;
	EEDR = data;
	SETBIT(EECR,EEMWE);
	SETBIT(EECR,EEWE);	
}