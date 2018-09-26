//LCD Functions Developed by LIGO GEORGE @ electroSome.com
//original files : https://electrosome.com/interfacing-lcd-atmega32-microcontroller-atmel-studio/
/*Additional develop made by Mohammed Essam Mahran (mhran9333@gmail.com)*/
//This driver is for 16x2 LCD (Used in 4 Pins Mode)

#define LOW		0
#define HIGH	1

#define F_CPU 8000000UL // 8 MHz clock speed
#include <util/delay.h>
#include <avr/io.h>
#include <avr/iom32.h>
#include <stdio.h>
#include "lcd.h"

void DataPinChange(uint8_t LCD_Pin , uint8_t State) //Change LCD Data pin state (HIGH or LOW)
{
	switch (State)
	{
		case HIGH:
		{
			LCD_PORT|=(1<<LCD_Pin);
			
		}break;
		
		case LOW:
		{
			LCD_PORT&=~(1<<LCD_Pin);
			
		}break;
	}
}

void ControlPinChange(uint8_t LCD_Control_Pin , uint8_t State) //Change LCD Control pin state (HIGH or LOW)
{
	switch (State)
	{
		case HIGH:
		{
			
			LCD_CTRL_PORT|=(1<<LCD_Control_Pin);
			
		}break;
		
		case LOW:
		{
			LCD_CTRL_PORT&=~(1<<LCD_Control_Pin);
			
		}break;
	}
}

void LCD4_Port(uint8_t a)							//LCD Data pins masking (sending data or command to LCD from AVR)
{
	if(a & 1)
	DataPinChange(D4,1);
	else
	DataPinChange(D4,0);
	
	if(a & 2)
	DataPinChange(D5,1);
	else
	DataPinChange(D5,0);
	
	if(a & 4)
	DataPinChange(D6,1);
	else
	DataPinChange(D6,0);
	
	if(a & 8)
	DataPinChange(D7,1);
	else
	DataPinChange(D7,0);
}
void LCD4_Command(uint8_t Command)					//Send command from AVR to LCD
{
	ControlPinChange(RS,0);             // => RS = 0
	LCD4_Port(Command);
	ControlPinChange(EN,1);            // => E = 1
	_delay_ms(1);
	ControlPinChange(EN,0);             // => E = 0
	_delay_ms(1);
}

void LCD4_Clear()									//Clear LCD
{
	LCD4_Command(0);
	LCD4_Command(1);
	_delay_ms(3);
}

void LCD4_Set_Cursor(uint8_t Row, uint8_t Column)	//Set cursor of LCD depending on Row and Column location (16X2 LCD) 16 columns , 2 rows		
{
	char temp,z,y;
	if(Row == 1)
	{
		temp = 0x80 + Column -1;
		z = temp>>4;
		y = (0x80+ Column -1) & 0x0F;
		LCD4_Command(z);
		LCD4_Command(y);
	}
	else if(Row == 2)
	{
		temp = 0xC0 + Column -1;
		z = temp>>4;
		y = (0xC0+Column -1) & 0x0F;
		LCD4_Command(z);
		LCD4_Command(y);
	}
}

void LCD4_Init()									//Initialize LCD (This function is first called in main() )
{
        /*TODO:
                change the DDRB and other stuff*/
        DDRB = 0xff;                       // setting DDR of PORT B
	LCD4_Port(0x00);
	_delay_ms(20);
	///////////// Reset process from datasheet /////////
	LCD4_Command(0x03);
	_delay_ms(5);
	LCD4_Command(0x03);
	_delay_ms(11);
	
	LCD4_Command(0x03);
	LCD4_Command(0x02);
	LCD4_Command(0x02);
	LCD4_Command(0x08);
	LCD4_Command(0x00);
	LCD4_Command(0x0C);
	LCD4_Command(0x00);
	LCD4_Command(0x06);
}

void LCD4_Write_Char(uint8_t Character)				//Write a character to LCD
{
	char temp,y;
	temp = Character&0x0F;
	y = Character&0xF0;
	ControlPinChange(RS,1);             // => RS = 1
	LCD4_Port(y>>4);             		//Data transfer
	ControlPinChange(EN,1);
	_delay_ms(1);
	ControlPinChange(EN,0);
	_delay_ms(1);
	LCD4_Port(temp);
	ControlPinChange(EN,1);
	_delay_ms(1);
	ControlPinChange(EN,0);
	_delay_ms(1);
}

void LCD4_Write_String(char *String)				//Write a string to LCD
{
	int i;
	for(i=0;String[i]!='\0';i++)
	LCD4_Write_Char(String[i]);
}

void LCD4_Write_Int(int Num){
       char str[32];
       
        sprintf (str, "%d", Num);
        LCD4_Write_String(str);
}
void LCD4_Write_Float(float Num){
        char str[32];
        char *tmpSign = (Num < 0) ? "-" : "";
        float tmpVal = (Num < 0) ? -Num : Num;

        int tmpInt1 = tmpVal;                  // Get the integer (678).
        float tmpFrac = tmpVal - tmpInt1;      // Get fraction (0.0123).
        int tmpInt2 = trunc(tmpFrac * 100);  // Turn into integer (123).

        // Print as parts, note that you need 0-padding for fractional bit.
        //
        sprintf (str, "%s%d.%02d", tmpSign, tmpInt1, tmpInt2);
        LCD4_Write_String(str);
}
void LCD4_Shift_Right()								//Shift LCD to right
{
	LCD4_Command(0x01);
	LCD4_Command(0x0C);
}

void LCD4_Shift_Left()								//Shift LCD to left
{
	LCD4_Command(0x01);
	LCD4_Command(0x08);
}
