
#define F_CPU 8000000UL // 8 MHz clock speed

#include <avr/interrupt.h>
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>

#include "keypad.h"


void keypadInit(void){

        
        keypadDDR = 0xF0;//taking column pins as input and row pins as output
        _delay_ms(1);
        keypadPORT = 0x0F;// powering the row ins
        _delay_ms(1);


}

char* keypadScan(void){
        int keypressed=0;//integer for storing matrix value
        
        if (keypadPIN != 0b11110000){
                //in any of column pins goes high execute the loop
                   
                //LCD4_Write_Float(PINC);
                //key++;
                // _delay_ms(5);

                keypressed = keypadPIN;//taking the column value into integer
                keypadDDR ^=0b11111111;//making rows as inputs and columns as ouput
                _delay_ms(1);
                keypadPORT ^= 0b11111111;//powering columns
                _delay_ms(1);
                keypressed |= keypadPIN;//taking row value and OR ing it to column value
                
                //LCD4_Write_Int(keypressed);
                       
                switch (keypressed){

                        case keypadCode_0:
                                return "0";
                        break;
                        case keypadCode_1:
                                return "1";                       
                        break;
                                        
                        case keypadCode_2:
                                return "2";
                        break;
                                        
                        case keypadCode_3:
                                return "3";
                        break;
                                        
                        case keypadCode_4:
                                return "4";
                        break;
                                        
                        case keypadCode_5:
                                return "5";
                        break;
                                        
                        case keypadCode_6:
                                return "6";
                        break;
                                        
                        case keypadCode_7:
                                return "7";
                        break;
                                        
                        case keypadCode_8:
                                return "8";
                        break;
                                        
                        case keypadCode_9:
                                return "9";
                        break;
                                        
                        case keypadCode_A:
                                return "A";
                        break;
                                        
                        case keypadCode_B:
                                return "B";
                        break;
                        
                        case keypadCode_C:
                                return "C";
                        break;
                                        
                        case keypadCode_D:
                                return "D";
                        break;
                                        
                        case keypadCode_S:
                                return "*";
                        break;
                                        
                        case keypadCode_H:
                                return "#";
                        break;                      
                }
               
                keypressed=0;//after showing integer erasing the row column memory
                keypadDDR ^=0b11111111;//shifting input and power port
                _delay_ms(1);
                keypadPORT ^= 0b11111111;//powering row pins of keypad
                _delay_ms(220);
                    
        }else
                return 0;
}

