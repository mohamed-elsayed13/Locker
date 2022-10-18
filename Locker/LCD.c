/*
 * LCD.c
 *
 * Created: 8/12/2022 5:06:44 PM
 *  Author: Mohamed Elsayed
 */ 
#include "LCD.h"
/*****************************************************************************
* Function Name: LCD_init
* Purpose      : Init lcd in 4 bit mode, clear lcd and turn off cursor
* Parameters   : void
* Return value : void
*****************************************************************************/
void LCD_init(void){
	INIT_LCD_PINS;
	LCD_write_command(0x3);
	_delay_ms(4);
	LCD_write_command(0x3);
	_delay_ms(4);	
	LCD_write_command(0x3);
	_delay_ms(4);
	LCD_write_command(0x2);
	LCD_write_command(0x28);
	LCD_write_command(0x08);
	LCD_write_command(0x01);
	LCD_write_command(0x06);
	LCD_write_command(0x0c);
	_delay_ms(20);
	
			
}
/*****************************************************************************
* Function Name: LCD_write_command
* Purpose      : Write command to LCD
* Parameters   : data : one of LCD commands
* Return value : void
*****************************************************************************/
void LCD_write_command(uint8_t data){
	RS(0);
	D7(GETBIT(data,7));
	D6(GETBIT(data,6));
	D5(GETBIT(data,5));
	D4(GETBIT(data,4));
	EN(1);
	_delay_ms(1);
	EN(0);
	_delay_ms(1);
	D7(GETBIT(data,3));
	D6(GETBIT(data,2));
	D5(GETBIT(data,1));
	D4(GETBIT(data,0));
	EN(1);
	_delay_ms(1);
	EN(0);
	_delay_ms(1);

}
/*****************************************************************************
* Function Name: LCD_write_data
* Purpose      : Write data on LCD
* Parameters   : data : Ascii symbol to be written on LCD
* Return value : void
*****************************************************************************/
void LCD_write_char(uint8_t data){
	RS(1);
	D7(GETBIT(data,7));
	D6(GETBIT(data,6));
	D5(GETBIT(data,5));
	D4(GETBIT(data,4));
	EN(1);
	_delay_ms(1);
	EN(0);
	_delay_ms(1);
	D7(GETBIT(data,3));
	D6(GETBIT(data,2));
	D5(GETBIT(data,1));
	D4(GETBIT(data,0));
	EN(1);
	_delay_ms(1);
	EN(0);
	_delay_ms(1);
	
}
/*****************************************************************************
* Function Name: LCD_write_string
* Purpose      : Write string on LCD
* Parameters   : *data : array of chars to be written on LCD
* Return value : void
*****************************************************************************/
void LCD_write_string(uint8_t* data){
	uint8_t i=0;
	while(data[i]!='\0'){
		LCD_write_char(data[i]);
		i++;
	}
}
/*****************************************************************************
* Function Name: LCD_write_num
* Purpose      : Write number on LCD
* Parameters   : data : 16 bit number to be written on LCD
* Return value : void
*****************************************************************************/
void LCD_write_num(uint32_t data){
	uint8_t num[10]={0}; // largest 16 bit number --> 65535 (5 digits) can be stored in this array
	int8_t i=0;
	if (data==0){		
		LCD_write_char('0');
		return;
	}
	else{
	while(data!=0){
		num[i]=(data%10)+48; // This will isolate the smallest digit
		data/=10;			// This will remove this digit from the whole number
		i++;
	}
	while(i>=0){
	LCD_write_char(num[i]);
	i--;	
	} 
	}
}

