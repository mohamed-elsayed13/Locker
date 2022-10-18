/*
 * KEYPAD.c
 *
 * Created: 8/13/2022 4:14:01 PM
 *  Author: Mohamed Elsayed
 */ 
#include "KEYPAD.h"
/*****************************************************************************
* Function Name: KEYPAD_init
* Purpose      : PotrB Pins from 4 to 7 pull up input & PortD Pins (2 to 5) output
* Parameters   : void
* Return value : void
*****************************************************************************/
void KEYPAD_init(void){
	INIT_KEYPAD_PINS
}
/*****************************************************************************
* Function Name: KEYPAD_read
* Purpose      : Read data from Keypad
* Parameters   : void
* Return value : Ascii symbol from matrix array of keypad
*****************************************************************************/
uint8_t KEYPAD_read(void){
	const uint8_t keypad_matrix[]={'7','8','9','/',
								   '4','5','6','*',
								   '1','2','3','-',
								   'c','0','=','+'};

	int i;
	for(i=0;i<4;i++){
	K2(i>0); K3(1>i); K4(2>i); K5(3>i);
	if(B4==0) return keypad_matrix[i+0];
	if(B5==0) return keypad_matrix[i+4];
	if(B6==0) return keypad_matrix[i+8];
	if(B7==0) return keypad_matrix[i+12];
	_delay_ms(1);
	}
	return 0;
	
}
