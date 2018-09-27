#define F_CPU 8000000UL

#include <avr/interrupt.h>
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>

#include "adc.h"
#include "lcd.h"
#include "keypad.h"
#include "mq2.h"
#include "lm35.h"
#include "output.h"
#include "menu.h"


Data_typedef g_data;
Menu_typedef g_menu;



char msg_welcome1[] =   "WELCOME";
char msg_welcome2[] =   " SMOKE-DETECTOR ";
char msg_welcome3[] =   "->MOHAMAD ZARE<-";
char msg_calib[] =      "CALIB ...";
char msg_ok[] =         "OK";
char msg_cancel[] =     "CANCEL";

                        

void welcome(void){
        LCD4_Clear();
        LCD4_Set_Cursor(1, 16);
        LCD4_Write_String(msg_welcome1);
        for(int i=0; i<10; i++){
                LCD4_Shift_Left();
                _delay_ms(100);
        }
        _delay_ms(1000);

        LCD4_Clear();
        LCD4_Set_Cursor(1, 16);
        LCD4_Write_String(msg_welcome2);
        LCD4_Set_Cursor(2, 16);
        LCD4_Write_String(msg_welcome3);
        for(int i=0; i<15; i++){
                LCD4_Shift_Left();
                _delay_ms(100);
        }                
        _delay_ms(2000);
}

void calib_mq2(void){

        LCD4_Clear();
        LCD4_Set_Cursor(1, 1);
        LCD4_Write_String(msg_calib);
        
        g_data.Ro = SensorCalibration(); 
        //init_sys();
        LCD4_Set_Cursor(1, 13);
        LCD4_Write_String(msg_ok);

        LCD4_Set_Cursor(2, 1);
        LCD4_Write_String("Ro = ");
        LCD4_Write_Float(g_data.Ro);
        LCD4_Write_String(" K-ohm");
        buzzer_on();
        _delay_ms(1000);  
        buzzer_off();

        _delay_ms(2000);
                        LCD4_Clear();
}



/*

*/
int pass_query(void){
        
        char pass[] = "1111";
        char query[5];
        int cnt=0;
     
        LCD4_Clear();
        LCD4_Set_Cursor(1, 4);
        LCD4_Write_String("PASSWORD");
        LCD4_Set_Cursor(2, 6);
         _delay_ms(300);
       
        g_data.keypad_ready = 0;  
        while(cnt < 4){
                if(g_data.keypad_ready){
                        LCD4_Write_Char('*');
                        buzzer_on();
                        _delay_ms(200);  
                        buzzer_off();
                        query[cnt] = g_data.keypad_last;
                        cnt++;
                        g_data.keypad_ready = 0;
                        
                }
                //buzzer_on();
                _delay_ms(500);  
                //buzzer_off();
        }
        query[4] = 0;
        
        if (strcmp(g_data.pass, query)){
                //if pass  NOT is correct
                LCD4_Clear();
                LCD4_Set_Cursor(1, 3);
                LCD4_Write_String("NOT CORRECT");
                buzzer_on();
                _delay_ms(500);  
                buzzer_off();
                _delay_ms(500);                  
                buzzer_on();
                _delay_ms(500);  
                buzzer_off();                
                _delay_ms(1500);
                return 1;
        }else{
                //if pass is correst
                LCD4_Clear();
                LCD4_Set_Cursor(1, 5);
                LCD4_Write_String("CORRECT");
                buzzer_on();
                _delay_ms(1000);  
                buzzer_off();
                _delay_ms(2000);
                return 0;
        }
        

}

int pass_set(void){
        
        char pass[] = "1111";
        char query1[5];
        char query2[5];
        int cnt=0;
     
        LCD4_Clear();
        LCD4_Set_Cursor(1, 2);
        LCD4_Write_String("NEW PASSWORD");
        LCD4_Set_Cursor(2, 6);
         _delay_ms(300);
       
        g_data.keypad_ready = 0;  
        while(cnt < 4){
                if(g_data.keypad_ready){
                        LCD4_Write_Char('*');
                        buzzer_on();
                        _delay_ms(200);  
                        buzzer_off();
                        query1[cnt] = g_data.keypad_last;
                        cnt++;
                        g_data.keypad_ready = 0;
                        
                }
                //buzzer_on();
                _delay_ms(500);  
                //buzzer_off();
        }
        query1[cnt] = 0;
        cnt=0;
        LCD4_Clear();
        LCD4_Set_Cursor(1, 5);
        LCD4_Write_String("AGAIN");
        LCD4_Set_Cursor(2, 6);
         _delay_ms(300);
       
        g_data.keypad_ready = 0;  
        while(cnt < 4){
                if(g_data.keypad_ready){
                        LCD4_Write_Char('*');
                        buzzer_on();
                        _delay_ms(200);  
                        buzzer_off();
                        query2[cnt] = g_data.keypad_last;
                        cnt++;
                        g_data.keypad_ready = 0;
                        
                }
                //buzzer_on();
                _delay_ms(500);  
                //buzzer_off();
        }
        query2[cnt] = 0;
        cnt=0;
                
        if (strcmp(query1, query2)){
                //if pass  NOT is correct
                LCD4_Clear();
                LCD4_Set_Cursor(1, 3);
                LCD4_Write_String("TRY AGAIN");
                buzzer_on();
                _delay_ms(500);  
                buzzer_off();
                _delay_ms(500);                  
                buzzer_on();
                _delay_ms(500);  
                buzzer_off();                
                _delay_ms(1500);
                return 1;
        }else{
                //if pass is correst
                LCD4_Clear();
                LCD4_Set_Cursor(1, 3);
                LCD4_Write_String("SET NEW PASS");
                strcpy(g_data.pass, query1);
                buzzer_on();
                _delay_ms(1000);  
                buzzer_off();
                _delay_ms(2000);
                return 0;
        }
        

}

int tel_set(void){
        

        char query1[9];

        int cnt=0;
     
        LCD4_Clear();
        LCD4_Set_Cursor(1, 6);
        LCD4_Write_String("TEL");
        LCD4_Set_Cursor(2, 3);
         _delay_ms(300);
       
        g_data.keypad_ready = 0;  
        while(cnt < 8){
                if(g_data.keypad_ready){
                        LCD4_Write_Char(g_data.keypad_last);
                        buzzer_on();
                        _delay_ms(200);  
                        buzzer_off();
                        query1[cnt] = g_data.keypad_last;
                        cnt++;
                        g_data.keypad_ready = 0;
                        
                }
                //buzzer_on();
                _delay_ms(500);  
                //buzzer_off();
        }
        query1[cnt] = 0;
        cnt=0;
                

        LCD4_Clear();
        LCD4_Set_Cursor(1, 3);
        LCD4_Write_String("->SAVE<-");

        strcpy(g_data.tel, query1);
        buzzer_on();
        _delay_ms(1000);  
        buzzer_off();
        _delay_ms(2000);
        return 0;
      

}

int max_mq2_set(void){
        

        char query1[9];

        int cnt=0;
     
        LCD4_Clear();
        LCD4_Set_Cursor(1, 2);
        LCD4_Write_String("LPG MAX PPM:");
        LCD4_Set_Cursor(2, 3);
         _delay_ms(300);
       
        g_data.keypad_ready = 0;  
        while(cnt < 9){
                if(g_data.keypad_ready){
                        if(g_data.keypad_last == 0x2A)
                                break;
                        LCD4_Write_Char(g_data.keypad_last);
                        buzzer_on();
                        _delay_ms(200);  
                        buzzer_off();
                        query1[cnt] = g_data.keypad_last;
                        cnt++;
                        g_data.keypad_ready = 0;
                        
                }
                //buzzer_on();
                _delay_ms(500);  
                //buzzer_off();
        }
        query1[cnt] = 0;
        cnt=0;
                
        g_data.ppm_lpg_max = atoi(query1);
        LCD4_Clear();
        LCD4_Set_Cursor(1, 3);
        LCD4_Write_String("->SAVE<-");
   
        buzzer_on();
        _delay_ms(1000);  
        buzzer_off();
        _delay_ms(1000);

        LCD4_Clear();
        LCD4_Set_Cursor(1, 2);
        LCD4_Write_String("SMOKE MAX PPM:");
        LCD4_Set_Cursor(2, 3);
         _delay_ms(300);
       
        g_data.keypad_ready = 0;  
        while(cnt < 9){
                if(g_data.keypad_ready){
                        if(g_data.keypad_last == 0x2A)
                                break;                
                        LCD4_Write_Char(g_data.keypad_last);
                        buzzer_on();
                        _delay_ms(200);  
                        buzzer_off();
                        query1[cnt] = g_data.keypad_last;
                        cnt++;
                        g_data.keypad_ready = 0;
                        
                }
                //buzzer_on();
                _delay_ms(500);  
                //buzzer_off();
        }
        query1[cnt] = 0;
        cnt=0;
                
        g_data.ppm_smoke_max = atoi(query1);
        LCD4_Clear();
        LCD4_Set_Cursor(1, 3);
        LCD4_Write_String("->SAVE<-");
   
        buzzer_on();
        _delay_ms(1000);  
        buzzer_off();
        _delay_ms(1000);
        
        LCD4_Clear();
        LCD4_Set_Cursor(1, 1);
        LCD4_Write_String("LM=");
        LCD4_Write_Int(g_data.ppm_lpg_max);   
        LCD4_Write_String("  SM=");
        LCD4_Write_Int(g_data.ppm_smoke_max);          
        buzzer_on();
        _delay_ms(500);  
        buzzer_off();
        _delay_ms(3000);        
        return 0;
      

}


int max_lm35_set(void){
     
        char query1[9];
        int cnt=0;
     
        LCD4_Clear();
        LCD4_Set_Cursor(1, 2);
        LCD4_Write_String("MAX TEMP:");
        LCD4_Set_Cursor(2, 3);
         _delay_ms(300);
       
        g_data.keypad_ready = 0;  
        while(cnt < 9){
                if(g_data.keypad_ready){
                        if(g_data.keypad_last == 0x2A)
                                break;
                        LCD4_Write_Char(g_data.keypad_last);
                        buzzer_on();
                        _delay_ms(200);  
                        buzzer_off();
                        query1[cnt] = g_data.keypad_last;
                        cnt++;
                        g_data.keypad_ready = 0;
                        
                }
                //buzzer_on();
                _delay_ms(500);  
                //buzzer_off();
        }
        query1[cnt] = 0;
        cnt=0;
                
        g_data.temp_max = atoi(query1);
        LCD4_Clear();
        LCD4_Set_Cursor(1, 3);
        LCD4_Write_String("->SAVE<-");
   
        buzzer_on();
        _delay_ms(1000);  
        buzzer_off();
        _delay_ms(1000);

        LCD4_Clear();
        LCD4_Set_Cursor(1, 1);
        LCD4_Write_String("MAX TEMP=");
        LCD4_Write_Int(g_data.temp_max);   
        
        buzzer_on();
        _delay_ms(500);  
        buzzer_off();
        _delay_ms(3000);                

}

void mq2_warning(void){


}

void lm35_warning(void){

}

void show_mq2_lm35(void){


        g_data.ppm_smoke = GetGasPercentage(ReadSensor()/g_data.Ro, SMOKE);
        g_data.ppm_lpg = GetGasPercentage(ReadSensor()/g_data.Ro, LPG);
        g_data.temp = lm35_get_temp()/10;

        //LCD4_Clear();
        //LCD4_Set_Cursor(1, 1);
        //LCD4_Write_String("              ");
        LCD4_Set_Cursor(1, 1);
        LCD4_Write_String("S=");
        LCD4_Write_Int(g_data.ppm_smoke);

        //LCD4_Set_Cursor(1, 6);
        LCD4_Write_String("   L=");
        LCD4_Write_Int(g_data.ppm_lpg);

        LCD4_Set_Cursor(2, 1);               
        LCD4_Write_String("temp: ");
        LCD4_Write_Int(g_data.temp);
        LCD4_Write_String("'C  ");
        
          _delay_ms(250);        
       
        
}


void in_loop(void){

        LCD4_Clear();
        LCD4_Set_Cursor(1, 1);
        LCD4_Write_String("REST THE DEVICE");

        
        while(1){
                buzzer_on();
                _delay_ms(500);  
                buzzer_off();
                _delay_ms(3000);
                
        }               

}

void state_machine(void){
        int cnt = 0;
        switch(g_data.next_menu){
        
                case MENU_1:
                        show_mq2_lm35();
                        g_data.next_menu = MENU_1;
                        //LCD4_Clear();
                break;
                
                case MENU_2:
                        while(pass_set());
                        while(tel_set());
                        g_data.next_menu = MENU_1;
                        LCD4_Clear();
                break;
                
                case MENU_3:
                        max_mq2_set();
                        max_lm35_set();
                        g_data.next_menu = MENU_1;
                        LCD4_Clear();
                break;
                
                case MENU_4:

                        welcome();
                        calib_mq2();
                        if(g_data.is_resigter){
                                
                                for(cnt=0; cnt<3; cnt++){
                                        if(!pass_query())
                                                break;
                                        
                                }
                                if(cnt >=2){
                                        g_data.next_menu = MENU_5;
                                        //return;        
                                }else{
                                        g_data.next_menu = MENU_1;
                                }
                                
                                
                        }
                        else{
                                g_data.next_menu = MENU_2;
                        }
                                
                        
                        LCD4_Clear();
                break;
                
                case MENU_5:
                        in_loop();
                        //g_data.next_menu = MENU_1;
                        //LCD4_Clear();
                break;
        }
        
        
        

}

void set_state(void){
        
        if(g_data.keypad_ready){
                
                switch(g_data.keypad_last){
                
                        case '1':
                                g_data.next_menu = MENU_1;    
                        break;
                        
                        case '2':
                                g_data.next_menu = MENU_2;    
                        break;
                        
                        case '3':
                                g_data.next_menu = MENU_3;       
                        break;
                        case '4':
                                g_data.next_menu = MENU_4;       
                        break; 
                        case '5':
                                g_data.next_menu = MENU_5;       
                        break;                        
                }
                                   
       }
}



