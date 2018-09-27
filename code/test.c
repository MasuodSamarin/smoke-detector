
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
#include "test.h"


void output_test(void){

        output_init();

        while(1){
                relay_on();
                buzzer_on();
                _delay_ms(1000);
                relay_off();
                buzzer_off();
                _delay_ms(1000);
        }
      
}

void keypad_test(void){

        int key=0;//allocating integer to reset the LCD once it reaches its display limit

        LCD4_Init();  // initialization of LCD function
        LCD4_Clear();
        _delay_ms(30);

        LCD4_Set_Cursor(1, 1);         // Go to the location 1,1 of lcd
        LCD4_Write_String("Press A key"); // Print the text
        LCD4_Set_Cursor(2, 1);         // Go to the location 1,2 of lcd




        keypadInit();
        char *chr;

        while(1){
                chr = keypadScan();
                if (chr){
                        LCD4_Write_String(chr);
                        key++;
                        _delay_ms(100);
                }
                if (key > 15){
                        key=0;
                        LCD4_Clear();
                        LCD4_Set_Cursor(1, 1);         // Go to the location 1,1 of lcd
                        LCD4_Write_String("Press A key"); // Print the text
                        LCD4_Set_Cursor(2, 1);         // Go to th
                        _delay_ms(1000);
                }
                
        }


}


void mq2_test(void){
        ADC_init();
        LCD4_Init();
      
        LCD4_Clear();
        LCD4_Set_Cursor(1, 1);
        LCD4_Write_String("Calib Ro ...");

        Ro = SensorCalibration();     //Please make sure the sensor is in clean air 
        LCD4_Set_Cursor(2, 1);
        LCD4_Write_String("COMPLETED..");
        _delay_ms(1000);
        
        LCD4_Clear();
        LCD4_Set_Cursor(1, 1);
        LCD4_Write_String("Ro: ");
        LCD4_Write_Float(Ro);
        LCD4_Write_String("  K-ohm");
        _delay_ms(1000);

        while(1)
        {
    
                float smoke = GetGasPercentage(ReadSensor()/Ro, SMOKE);
                float lpg = GetGasPercentage(ReadSensor()/Ro, LPG);
                float temp = lm35_get_temp()/10;

                //LCD4_Clear();
                //LCD4_Set_Cursor(1, 1);
                //LCD4_Write_String("              ");
                LCD4_Set_Cursor(1, 1);
                LCD4_Write_String("S=");
                LCD4_Write_Float(smoke);

                //LCD4_Set_Cursor(1, 6);
                LCD4_Write_String("   L=");
                LCD4_Write_Float(lpg);
                
                LCD4_Set_Cursor(2, 1);               
                LCD4_Write_String("temp: ");
                LCD4_Write_Float(temp);
                LCD4_Write_String("'C  ");
        }
}

void lm35_test(void){
        ADC_init();
        LCD4_Init();

        LCD4_Clear();
        LCD4_Set_Cursor(1, 1);
        LCD4_Write_String("temp: ");

        while(1){
                float t = lm35_get_temp();
                /*LCD4_Clear();
                LCD4_Set_Cursor(1, 1);
                LCD4_Write_String("temp: ");
                LCD4_Write_Float(t);
                _delay_ms(1000);*/
        }
}
     
