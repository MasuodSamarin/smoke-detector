// Counts for how long the machine has been running

float LPGCurve[3] = {2.3,0.20,-0.45};   //two points from LPG curve are taken point1:(200,1.6) point2(10000,0.26)
                                                    //take log of each point (lg200, lg 1.6)=(2.3,0.20)  (lg10000,lg0.26)=(4,-0.58)
                                                    //find the slope using these points. take point1 as reference   
                                                    //data format:{ x, y, slope};  

float SmokeCurve[3] = {2.3,0.53,-0.43};    //two points from smoke curve are taken point1:(200,3.4) point2(10000,0.62) 
                                                    //take log of each point (lg200, lg3.4)=(2.3,0.53)  (lg10000,lg0.63)=(4,-0.20)
                                                    //find the slope using these points. take point1 as reference   
                                                    //data format:{ x, y, slope};
														                                                  
float Ro = 10;  //Ro is initialized to 10 kilo ohms
 
char str[16];
int res;

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




void init_sys(void);

int main(void)

{
        init_sys();
        
        welcome(&g_data);
        //keypad_test();
        //mq2_test();
        //output_test();      
        //lm35_test();      
        
        while(1){
        
                //this is main loop of system
                
        } 
       
}

/*
 * system initilize of whole of system
 */
void init_sys(void){

        LCD4_Init();
        keypadInit();
        output_init();
        ADC_init();
        //lm35_init();
        //mq2_init();
}
   



