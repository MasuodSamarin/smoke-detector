#ifndef F_CPU
#define F_CPU 8000000UL // or whatever may be your frequency
#endif


#include <avr/io.h>
#include <util/delay.h>                // for _delay_ms()
#include "adc.h"
#include "lm35.h"
#include "lcd.h"



float lm35_get_temp(void){
        
        long int raw1, raw2, i;
        raw1=0; 
        raw2=0;
                 
        
        float temp=0;
        const int cnt = 200;
        

        for (i=0;i<cnt;i++) {  //take multiple samples and calculate the average value
          
                raw1 += (ADC_read(LM35_ch1) * ADC_OFFSET);
                _delay_ms(1);
        }
        raw1 = (raw1 / (cnt));  
        //ch1 = raw1 * temp_factor;

        for (i=0;i<cnt;i++) {  //take multiple samples and calculate the average value
          
                raw2 += (ADC_read(LM35_ch2) * ADC_OFFSET);
                _delay_ms(1);
        }
        raw2 = (raw2 / (cnt));  
        //ch2 = raw2 * temp_factor;

        
        //A1 = ADC_read(1);
        //A2 = ADC_read(2);
        
        temp = ((float)(raw1) - (float)(raw2)) * temp_factor;
        
        //LCD4_Clear();
        
 /*       LCD4_Set_Cursor(1, 1);
        LCD4_Write_String("t=");
        LCD4_Write_Float(temp);
        LCD4_Write_String("    ");               

        LCD4_Set_Cursor(2, 1);
        LCD4_Write_String("R1=");
        LCD4_Write_Int(raw1);


        LCD4_Write_String("  R2=");
        LCD4_Write_Int(raw2);
        LCD4_Write_String("    ");        
        _delay_ms(100);
     
        _delay_ms(100);
*/
        return temp;
        
}

