#ifndef F_CPU
#define F_CPU 8000000UL // or whatever may be your frequency
#endif


#include <avr/io.h>
#include <util/delay.h>                // for _delay_ms()
#include "adc.h"
#include "lm35.h"
#include "lcd.h"



float lm35_get_temp(void){
        
        long int A1, A2, i;
        float temp;
        
        const int cnt = 5;
        
        A1=0;
        for (i=0;i<cnt;i++) {  //take multiple samples and calculate the average value
          
                A1 += ADC_read(3);
                _delay_ms(5);
        }
        A1 = A1/(cnt);  
        
        A2=0;                
        for (i=0;i<cnt;i++) {  //take multiple samples and calculate the average value
          
                A2 += ADC_read(4);
                _delay_ms(5);
        }
        A2 = A2/(cnt);                         
   

        
        //A1 = ADC_read(1);
        //A2 = ADC_read(2);
        
        temp = (float)(A1 - A2);
        
        LCD4_Clear();
        
        LCD4_Set_Cursor(1, 1);
        LCD4_Write_String("A1=");
        LCD4_Write_Float(A1 * temp_factor);
               
        LCD4_Set_Cursor(2, 1);
        LCD4_Write_String("A2=");
        LCD4_Write_Float(A2 * temp_factor);
        

        return temp;
        
}

