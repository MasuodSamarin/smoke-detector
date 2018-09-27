
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

char keypadScan(void){
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
                                return 0x30;
                        break;
                        case keypadCode_1:
                                return 0x31;                       
                        break;
                                        
                        case keypadCode_2:
                                return 0x32;
                        break;
                                        
                        case keypadCode_3:
                                return 0x33;
                        break;
                                        
                        case keypadCode_4:
                                return 0x34;
                        break;
                                        
                        case keypadCode_5:
                                return 0x35;
                        break;
                                        
                        case keypadCode_6:
                                return 0x36;
                        break;
                                        
                        case keypadCode_7:
                                return 0x37;
                        break;
                                        
                        case keypadCode_8:
                                return 0x38;
                        break;
                                        
                        case keypadCode_9:
                                return 0x39;
                        break;
                                        
                        case keypadCode_A:
                                return 0x41;
                        break;
                                        
                        case keypadCode_B:
                                return 0x42;
                        break;
                        
                        case keypadCode_C:
                                return 0x43;
                        break;
                                        
                        case keypadCode_D:
                                return 0x44;
                        break;
                                        
                        case keypadCode_S:
                                return 0x2A;
                        break;
                                        
                        case keypadCode_H:
                                return 0x23;
                        break;                      
                }
               
                keypressed=0;//after showing integer erasing the row column memory
                keypadDDR ^=0b11111111;//shifting input and power port
                _delay_ms(1);
                keypadPORT ^= 0b11111111;//powering row pins of keypad
                _delay_ms(1);
                    
        }else
                return 0;
}

