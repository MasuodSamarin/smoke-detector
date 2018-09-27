
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


extern Data_typedef g_data;
extern Menu_typedef g_menu;

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
        char chr;

        while(1){
                chr = keypadScan();
                if (chr){
                        LCD4_Write_Char(chr);
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

        g_data.Ro = SensorCalibration();     //Please make sure the sensor is in clean air 
        LCD4_Set_Cursor(2, 1);
        LCD4_Write_String("COMPLETED..");
        _delay_ms(1000);
        
        LCD4_Clear();
        LCD4_Set_Cursor(1, 1);
        LCD4_Write_String("Ro: ");
        LCD4_Write_Float(g_data.Ro);
        LCD4_Write_String("  K-ohm");
        _delay_ms(1000);

        while(1)
        {
    
                float smoke = GetGasPercentage(ReadSensor()/g_data.Ro, SMOKE);
                float lpg = GetGasPercentage(ReadSensor()/g_data.Ro, LPG);
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
     
     
     
void keypad_talk_back(void){
        
        static int cnt=0;
        if(g_data.keypad_ready){
                g_data.keypad_ready = 0;
                cnt++;
                //LCD4_Clear();
                //LCD4_Set_Cursor(1, 1);
                LCD4_Write_Char(g_data.keypad_last);
                
                //data->Ro = SensorCalibration(); 
                //init_sys();
                //LCD4_Set_Cursor(1, 13);
                //LCD4_Write_String(msg_ok);
                
                _delay_ms(300);  
        }
        if(cnt > 15){
                LCD4_Clear();
                LCD4_Set_Cursor(1, 1);
                cnt=0;        
        }

}
