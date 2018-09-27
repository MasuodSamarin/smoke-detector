
#ifndef MY_KEYPAD_H_
#define MY_KEYPAD_H_

#define keypadDDR       DDRC
#define keypadPORT      PORTC
#define keypadPIN       PINC
#define keypad_PIN_0    0
#define keypad_PIN_1    1
#define keypad_PIN_2    2
#define keypad_PIN_3    3
#define keypad_PIN_4    4
#define keypad_PIN_5    5
#define keypad_PIN_6    6
#define keypad_PIN_7    7


#define keypadCode_0    235
#define keypadCode_1    119
#define keypadCode_2    123
#define keypadCode_3    125
#define keypadCode_4    183
#define keypadCode_5    187
#define keypadCode_6    189
#define keypadCode_7    215
#define keypadCode_8    219
#define keypadCode_9    221
#define keypadCode_A    126
#define keypadCode_B    190
#define keypadCode_C    222
#define keypadCode_D    238
#define keypadCode_S    231
#define keypadCode_H    237


void keypadInit(void);
char keypadScan(void);

#endif
