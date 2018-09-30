#ifndef MY_OUTPUT_H_
#define MY_OUTPUT_H_

#define OUTPUT_DDR      DDRD
#define OUTPUT_PORT     PORTD



#define BUZZER_DDR      DDRD
#define BUZZER_PORT     PORTD
#define BUZZER_PIN      6

#define RELAY_DDR       DDRD
#define RELAY_PORT      PORTD
#define RELAY_PIN       7



void output_init(void);
void buzzer_toggle(void);
void buzzer_on(void);
void buzzer_off(void);
void relay_toggle(void);
void relay_on(void);
void relay_off(void);

#endif

