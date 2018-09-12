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
#define F_CPU 16000000UL // or whatever may be your frequency
#endif
 
#include <avr/io.h>                    // adding header files
#include <util/delay.h>                // for _delay_ms()
 
int main(void)
{
   DDRC = 0x01;                       // setting DDR of PORT C
   while(1)
   {
       // LED on
       PORTC = 0b00000001;            // PC0 = High = LED attached on PC0 is ON
       _delay_ms(500);                // wait 500 milliseconds
 
       //LED off
       PORTC = 0b00000000;            // PC0 = Low = LED attached on PC0 is OFF
       _delay_ms(500);                // wait 500 milliseconds
   }
}
