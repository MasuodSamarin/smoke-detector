#ifndef F_CPU
#define F_CPU 8000000UL // or whatever may be your frequency
#endif


#include <avr/io.h>
#include <util/delay.h>                // for _delay_ms()
#include "output.h"



void output_init(void){
        OUTPUT_DDR = 0xff;
}

void buzzer_toggle(void){
        
        BUZZER_PORT ^= (1<<BUZZER_PIN);
}


void buzzer_on(void){
        
        BUZZER_PORT |= (1<<BUZZER_PIN);
}

void buzzer_off(void){
 
        BUZZER_PORT &=~ (1<<BUZZER_PIN);
}

void relay_toggle(void){
        RELAY_PORT ^= (1<<RELAY_PIN);
}

void relay_on(void){
        
        RELAY_PORT |= (1<<RELAY_PIN);
}

void relay_off(void){
     
        RELAY_PORT &=~ (1<<RELAY_PIN);
}


