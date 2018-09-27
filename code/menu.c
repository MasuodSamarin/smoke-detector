#define F_CPU 8000000UL

#include <avr/interrupt.h>
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>

#include "adc.h"
#include "lcd.h"
#include "keypad.h"
#include "mq2.h"
#include "lm35.h"
#include "output.h"
#include "menu.h"


Data_typedef g_data;
Menu_typedef g_menu;



char welcome_massegae1[] = "WELCOME";
char welcome_massegae2[] = " SMOKE-DETECTOR";
char welcome_massegae3[] = "->MOHAMAD ZARE<-";
void welcome(Data_typedef *data){

        while(1){
                /*
                for(int i=0; i<7; i++){
                        LCD4_Set_Cursor(1, 16);
                        LCD4_Write_Char(welcome_massegae2[i]);
                        _delay_ms(350);
                        LCD4_Shift_Left();
                }*/
                LCD4_Clear();
                LCD4_Set_Cursor(1, 16);
                LCD4_Write_String(welcome_massegae1);
                //_delay_ms(500);
                for(int i=0; i<10; i++){
                        LCD4_Shift_Left();
                        _delay_ms(100);
                }
                _delay_ms(1000);
                LCD4_Clear();
                LCD4_Set_Cursor(1, 10);
                LCD4_Write_String(welcome_massegae2);
                LCD4_Set_Cursor(2, 10);
                LCD4_Write_String(welcome_massegae3);
                                
                //_delay_ms(500);
                for(int i=0; i<9; i++){
                        LCD4_Shift_Left();
                        _delay_ms(100);
                }                
                _delay_ms(2000);
        }
        
     

}




