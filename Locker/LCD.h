/*
 * LCD.h
 *
 * Created: 8/12/2022 5:07:04 PM
 *  Author: Mohamed Elsayed
 */ 


#ifndef LCD_H_
#define LCD_H_
#include "STD_MACROS.h"
#define INIT_LCD_PINS DDRA |= 0b01111110
#define RS(x) if(x==1){SETBIT(PORTA,1);} else{CLRBIT(PORTA,1);}
#define EN(x) if(x==1){SETBIT(PORTA,2);} else{CLRBIT(PORTA,2);}
#define D7(x) if(x==1){SETBIT(PORTA,6);} else{CLRBIT(PORTA,6);}
#define D6(x) if(x==1){SETBIT(PORTA,5);} else{CLRBIT(PORTA,5);}
#define D5(x) if(x==1){SETBIT(PORTA,4);} else{CLRBIT(PORTA,4);}
#define D4(x) if(x==1){SETBIT(PORTA,3);} else{CLRBIT(PORTA,3);}
						 
void LCD_init(void);
void LCD_write_command(uint8_t);
void LCD_write_char(uint8_t);
void LCD_write_string(uint8_t*);
void LCD_write_num(uint32_t);




#endif /* LCD_H_ */
