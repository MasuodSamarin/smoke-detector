//LCD Functions Developed by LIGO GEORGE @ electroSome.com
//original files : https://electrosome.com/interfacing-lcd-atmega32-microcontroller-atmel-studio/
/*Additional develop made by Mohammed Essam Mahran (mhran9333@gmail.com)*/
//This driver is for 16x2 LCD (Used in 4 Pins Mode)

#ifndef LCD4_16x2_H_
#define LCD4_16x2_H_

//Data and control ports/pins configuration (Configured by user due to hardware connections)
#define LCD_PORT        PORTB
#define LCD_CTRL_PORT   PORTB
#define LCD_CTRL_DIR    DDRB

#define D7 PINB7
#define D6 PINB6
#define D5 PINB5
#define D4 PINB4

#define RS PINB0
#define RW PINB1
#define EN PINB2

void DataPinChange(uint8_t LCD_Pin , uint8_t State);								//Change LCD Data pin state (HIGH or LOW)
void ControlPinChange(uint8_t LCD_Control_Pin , uint8_t State);  					//Change LCD Control pin state (HIGH or LOW)
void LCD4_Port(uint8_t a);															//LCD Data pins masking (sending data or command to LCD from AVR)
void LCD4_Command(uint8_t Command);													//Send command from AVR to LCD
void LCD4_Clear();																	//Clear LCD
void LCD4_Set_Cursor(uint8_t Row, uint8_t Column);									//Set cursor of LCD depending on Row and Column location (16X2 LCD) 16 columns , 2 rows
void LCD4_Init();																	//Initialize LCD (This function is first called in main() )
void LCD4_Write_Char(uint8_t Character);											//Write a character to LCD
void LCD4_Write_String(char *String);   //Write a string to LCD
void LCD4_Write_Int(int Num);
void LCD4_Write_Float(float Num);												
void LCD4_Shift_Right();															//Shift LCD to right
void LCD4_Shift_Left();																//Shift LCD to left

#endif //LCD4_16x2_H_
