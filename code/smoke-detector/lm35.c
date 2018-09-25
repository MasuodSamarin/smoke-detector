#ifndef F_CPU
#define F_CPU 8000000UL // or whatever may be your frequency
#endif


#include <avr/io.h>
#include <util/delay.h>                // for _delay_ms()
#include "adc.h"
#include "lm35.h"
#include "lcd.h"



float lm35_get_temp(void){
        
        uint32_t A0, A1, i;
        float temp;
        
        const int factor = 50;
  
        for (i=0;i<factor;i++) {  //take multiple samples and calculate the average value
          
                A0 += ADC_read(LM35_ch1);
                _delay_ms(5);
        }
        A0 = A0/factor;  
                        
        for (i=0;i<factor;i++) {  //take multiple samples and calculate the average value
          
                A1 += ADC_read(LM35_ch2);
                _delay_ms(5);
        }
        A1 = A1/factor;                         
       
        temp = (float)(A0 - A1) * temp_factor;
        
        LCD4_Clear();
        LCD4_Set_Cursor(1, 1);
        LCD4_Write_String("A0= ");
        LCD4_Write_Int(A0);
        LCD4_Write_String("  A1= ");
        LCD4_Write_Int(A1);
        LCD4_Set_Cursor(2, 1);
        LCD4_Write_Int((A0 - A1));
        LCD4_Write_String("     ");
        return temp;
        
}

