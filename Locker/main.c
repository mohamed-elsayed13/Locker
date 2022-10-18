/*
 * Locker.c
 *
 * Created: 8/20/2022 8:53:02 PM
 * Author : Mohamed Elsayed
 */ 

#include "LCD.h"
#include "KEYPAD.h"
#include "EEPROM.h"
uint8_t password[10];
uint8_t digit_flag=0;
uint8_t change_flag=0;
void check_reset(void);
void read_digit(void);
void check_password(void);
int main(void)
{
    LCD_init();
	KEYPAD_init();
	SETBIT(DDRC,0); // for Buzzer
	SETBIT(DDRC,1); // for locker
	LCD_write_command(0x80);
	LCD_write_string("Enter Password");
	while (1) 
    {
		for(uint8_t i=0;i<4;i++){
		if(change_flag==0 && digit_flag==4 && GETBIT(PORTC,1)==0){
			check_password();
			}
		while(KEYPAD_read()==0){}
		read_digit();
		SETBIT(PORTC,0);
		_delay_ms(500);
		CLRBIT(PORTC,0);
		}
		
    }
}

void read_digit(void){
	switch(KEYPAD_read()){
		case '+':
		break;
		case '-':
		break;
		case '/':
		if(change_flag==0){
		SETBIT(PORTC,0);
		_delay_ms(3000);
		CLRBIT(PORTC,0);
		LCD_write_command(0x1);
		LCD_write_command(0x80);
		LCD_write_string("Enter new password");
		LCD_write_command(0x0c);
		digit_flag=0;
		change_flag++;
		}
		else if(change_flag==1){
			EEPROM_write(50,password[0]-48);
			EEPROM_write(51,password[1]-48);
			EEPROM_write(52,password[2]-48);
			EEPROM_write(53,password[3]-48);
			LCD_write_command(0x1);
			LCD_write_command(0x80);
			LCD_write_string("Password Changed");
			digit_flag=0;
			change_flag=0;
		}
		break;
		case '*':		
		if(GETBIT(PORTC,1)==1){	//locker is open
		CLRBIT(PORTC,1);
		LCD_write_command(0x1);
		LCD_write_command(0x80);
		LCD_write_string("Enter Password");
		digit_flag=0;
		}
		break;
		case '=':
		break;
		case 'c':
		break;
		default:
		if(digit_flag==0 && GETBIT(PORTC,1)==0){
			LCD_write_command(0xc0);
			LCD_write_char('*');
			password[0]=KEYPAD_read();
			digit_flag++;
		}
		else if(digit_flag==1 && GETBIT(PORTC,1)==0){
			LCD_write_char('*');
			password[1]=KEYPAD_read();
			digit_flag++;
		}
		else if(digit_flag==2 && GETBIT(PORTC,1)==0){
			LCD_write_char('*');
			password[2]=KEYPAD_read();
			digit_flag++;
		}
		else if(digit_flag==3&& GETBIT(PORTC,1)==0){
			LCD_write_char('*');
			password[3]=KEYPAD_read();
			digit_flag++;
		}
		else if(digit_flag<10 && GETBIT(PORTC,1)==1){
			if(digit_flag==0) LCD_write_command(0xc0);
			LCD_write_char('*');
			password[digit_flag]=KEYPAD_read();
			digit_flag++;
		}				
		else if(digit_flag==10){
			check_reset();
			digit_flag=0;
		}
		break;
	}
	}
void check_password(void){
	if(digit_flag==4){
		if (password[0]-48==EEPROM_read(50) && password[1]-48==EEPROM_read(51) && password[2]- 48==EEPROM_read(52) && password[3]- 48==EEPROM_read(53)){
			SETBIT(PORTC,1);
			LCD_write_command(0x1);
			LCD_write_command(0x80);
			LCD_write_string("Locker is open");
			digit_flag=0;
		}
		else{
			LCD_write_command(0x1);
			LCD_write_command(0x80);
			LCD_write_string("Wrong, try again!");
			SETBIT(PORTC,0);
			_delay_ms(3000);
			CLRBIT(PORTC,0);
			LCD_write_command(0xc0);
			digit_flag=0;
		}
	}
}
void check_reset(void){
	uint8_t i;
	for(uint8_t i=0;i<10;i++){
	if(password[i]-48==0){}
	else{
		digit_flag=0;
		break;
	}
	}
	if(digit_flag!=0){
		EEPROM_write(50,0);
		EEPROM_write(51,0);
		EEPROM_write(52,0);
		EEPROM_write(53,0);
		LCD_write_command(0x1);
		LCD_write_string("Password Changed");
		LCD_write_command(0xc0);
		digit_flag=0;
	}
}	
