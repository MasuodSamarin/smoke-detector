// Counts for how long the machine has been running

float LPGCurve[3] = {2.3,0.20,-0.45};   //two points from LPG curve are taken point1:(200,1.6) point2(10000,0.26)
                                                    //take log of each point (lg200, lg 1.6)=(2.3,0.20)  (lg10000,lg0.26)=(4,-0.58)
                                                    //find the slope using these points. take point1 as reference   
                                                    //data format:{ x, y, slope};  

float SmokeCurve[3] = {2.3,0.53,-0.43};    //two points from smoke curve are taken point1:(200,3.4) point2(10000,0.62) 
                                                    //take log of each point (lg200, lg3.4)=(2.3,0.53)  (lg10000,lg0.63)=(4,-0.20)
                                                    //find the slope using these points. take point1 as reference   
                                                    //data format:{ x, y, slope};
														                                                  
//float Ro = 10;  //Ro is initialized to 10 kilo ohms
 
char str[16];
int res;




#define F_CPU 8000000UL

#include <avr/interrupt.h>
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>

#include "tim.h"
#include "eeprom.h"
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


void init_sys(void);
void keypad_handler(void);
void init_timer(void);

/*
char eep1[20] = "HELLO";
char eep2[20];
*/

int main(void)

{
        init_sys();
        init_timer();

        //keypad_test();
        //mq2_test();
        //output_test();      
        //lm35_test();      
         
                        
      
        
        LCD4_Init();  // initialization of LCD function
        LCD4_Clear();
        LCD4_Set_Cursor(1, 1);         // Go to the location 1,1 of lcd
        LCD4_Write_String("HELLO"); // Print the text
        _delay_ms(1000);
        LCD4_Clear();
        
        g_data.is_resigter = 1;
        strcpy(g_data.pass, "1111");
        g_data.next_menu = MENU_4;
        //calib_mq2();        
        //while(pass_set());
        //while(tel_set());
        //swhile(max_mq2_set());
        
        while(1){
        
                //this is main loop of system
                //welcome(&g_data);
                //calib_mq2(&g_data);
                //keypad_talk_back();

                //pass_query();
                set_state();
                state_machine();
                //show_mq2_lm35();
        } 
       
}



void keypad_handler(void){

        char key = keypadScan();
        if( key){// && (g_data.keypad_ready)){
                g_data.keypad_last = key;
                g_data.keypad_ready = 1;
                
        }
}

/*
 * init the timer0 counter to interrupt. and call the keypad_handler
 * in periodically to handle the keypad request
 */
void init_timer(void){

        TIMER_Init(TIMER_0, TIMER0_MAX_DELAY);
        TIMER_AttachInterrupt(TIMER_0, keypad_handler);
        TIMER_Start(TIMER_0);
        sei();
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
   

/*
        EEPROM_WriteByte(0x00, 10);
        uint8_t r = EEPROM_ReadByte(0x00);
        if(r == 10){
                LCD4_Set_Cursor(1, 1);         // Go to the location 1,1 of lcd
                LCD4_Write_String("OKOKOK"); // Print the text     
                _delay_ms(3000);  
        }
        EEPROM_WriteString(0x00, eep1);
        EEPROM_ReadString(0x02, eep2);
        LCD4_Init();  // initialization of LCD function
        LCD4_Clear();
        LCD4_Set_Cursor(1, 1);         // Go to the location 1,1 of lcd
        LCD4_Write_String(eep1); // Print the text
        LCD4_Set_Cursor(2, 1);         // Go to the location 1,2 of lcd
        LCD4_Write_String(eep2); // Print the text
        _delay_ms(3000);
                        
*/               

