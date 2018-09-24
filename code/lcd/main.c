/*=====================================================
|   TASK:  TOGGLING THE LED ATTACHED TO A PARTICULAR PORT
|   DIFFICULTY LEVEL: VERY BASIC
|   Author:  BISWARUP BANERJEE
|   Language:  EMBEDDED C
|   To Compile:  RUN THE SCRIPT AS MENTIONED BY THE AUTHOR
|
|   Date:  June 2017
|
================================================*/
#ifndef F_CPU
#define F_CPU 8000000UL // or whatever may be your frequency
#endif

#include <avr/io.h>                    // adding header files
#include <util/delay.h>                // for _delay_ms()
#include <stdio.h>

#include "lcd.h"
#include "mq2.h"

extern float LPGCurve[3];// = {2.3,0.20,-0.45};   //two points from LPG curve are taken point1:(200,1.6) point2(10000,0.26)
                                                    //take log of each point (lg200, lg 1.6)=(2.3,0.20)  (lg10000,lg0.26)=(4,-0.58)
                                                    //find the slope using these points. take point1 as reference   
                                                    //data format:{ x, y, slope};  

extern float SmokeCurve[3];// = {2.3,0.53,-0.43};    //two points from smoke curve are taken point1:(200,3.4) point2(10000,0.62) 
                                                    //take log of each point (lg200, lg3.4)=(2.3,0.53)  (lg10000,lg0.63)=(4,-0.20)
                                                    //find the slope using these points. take point1 as reference   
                                                    //data format:{ x, y, slope};
														                                                  
extern float Ro;// = 10;  //Ro is initialized to 10 kilo ohms
 
char r[20];
int res;

int main(void)
{

    DDRB = 0xff;                       // setting DDR of PORT B
    //DDRA = 0x00;                       // setting DDR of PORT A

    LCD4_Init();
    LCD4_Clear();
    LCD4_Set_Cursor(1, 1);
    LCD4_Write_String("Hello");
    
    ADC_init();
    //Ro = SensorCalibration();                       //Please make sure the sensor is in clean air 
    
    while(1)
    {
        //int res = GetGasPercentage(ReadSensor()/Ro,LPG);

        LCD4_Clear();

        LCD4_Set_Cursor(0, 0);
        res= ADC_read(0);
        sprintf(r, "mq2:%d", res);
        LCD4_Write_String(r);
 
        LCD4_Set_Cursor(2, 0);
        int adc1 = ADC_read(1);
        int adc2 = ADC_read(2);
        sprintf(r, "(%d-%d)=%d", adc1, adc2, adc1-adc2);
        LCD4_Write_String(r);
        

       
        
        
        // LED on
        //PORTD = 0x80;            // PC0 = High = LED attached on PC0 is ON
        _delay_ms(500);                // wait 500 milliseconds
 
        //LED off
        //PORTD = 0x00;            // PC0 = Low = LED attached on PC0 is OFF
        _delay_ms(500);                // wait 500 milliseconds
    }
}
