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


void keypad_test(void);
void mq2_test(void);
void output_test(void);
void lm35_test(void);


int main(void)

{


        //keypad_test();
        //mq2_test();
        //output_test();      
        lm35_test();       
       
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
                LCD4_Write_Float(t);*/
                _delay_ms(1000);
        }
}
   
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
        LCD4_Init();
        LCD4_Clear();
        LCD4_Set_Cursor(1, 1);
        LCD4_Write_String("Calib Ro ...");

        ADC_init();

        Ro = SensorCalibration();     //Please make sure the sensor is in clean air 

        LCD4_Clear();
        LCD4_Set_Cursor(1, 1);
        LCD4_Write_String("Ro: ");
        LCD4_Write_Float(Ro);
        LCD4_Write_String("  K-ohm");

        _delay_ms(1000);

        while(1)
        {
    
                float smoke = GetGasPercentage(ReadSensor()/Ro,SMOKE);
                float lpg = GetGasPercentage(ReadSensor()/Ro,LPG);


                //LCD4_Clear();
                //LCD4_Set_Cursor(1, 1);
                //LCD4_Write_String("              ");
                LCD4_Set_Cursor(1, 1);
                LCD4_Write_String("S=");
                LCD4_Write_Float(smoke);

                //LCD4_Set_Cursor(1, 6);
                LCD4_Write_String("   L=");
                LCD4_Write_Float(lpg);

        }
}
     
/*
int main() {
 // DDRD = 0xFF; // Setting DDRD to output // setting for port D
  LCD4_Init();  // initialization of LCD function
  LCD4_Clear();
  _delay_ms(30);

  LCD4_Set_Cursor(1, 1);         // Go to the location 1,1 of lcd
  LCD4_Write_String("Press a key"); // Print the text
  LCD4_Set_Cursor(1, 2);         // Go to the location 1,2 of lcd

  // Keypad initialization
  keypadDirectionRegisterR = (1<<keypad_R_0) | (1<<keypad_R_1) | (1<<keypad_R_2) | (1<<keypad_R_3);
  keypadDirectionRegisterC = (0<<keypad_C_0) | (0<<keypad_C_1) | (0<<keypad_C_2) | (0<<keypad_C_3);

  keypadPortControlR = (0<<keypad_R_0) | (0<<keypad_R_1) | (0<<keypad_R_2) | (0<<keypad_R_3);
  keypadPortControlC = (1<<keypad_C_0) | (1<<keypad_C_1) | (1<<keypad_C_2) | (1<<keypad_C_3);
  
  while (1) {
      //LCD4_Clear();
      LCD4_Set_Cursor(1, 1);         // Go to the location 1,1 of lcd
      LCD4_Write_String("Press a key"); // Print the text
      LCD4_Set_Cursor(2, 1);         
      keypadScan();
      _delay_ms(500);
    
    /*
     DDRD = 0xff;                       // setting DDR of PORT B

        //LED on
        PORTD = 0x80;            // PC0 = High = LED attached on PC0 is ON
        _delay_ms(500);                // wait 500 milliseconds

        //LED off
        PORTD = 0x00;            // PC0 = Low = LED attached on PC0 is OFF
        _delay_ms(500);                // wait 500 milliseconds
 /*       */
 /* };

  return 0;
}
*/
/*
void keypadScan(){
  
  // Store value for column
  uint8_t keyPressCodeC = keypadPortValueC;
  
      keypadDirectionRegisterC ^= (1<<keypad_C_0) | (1<<keypad_C_1) | (1<<keypad_C_2) | (1<<keypad_C_3);
      keypadDirectionRegisterR ^= (1<<keypad_R_0) | (1<<keypad_R_1) | (1<<keypad_R_2) | (1<<keypad_R_3); 
  
      keypadPortControlC ^= (1<<keypad_C_0) | (1<<keypad_C_1) | (1<<keypad_C_2) | (1<<keypad_C_3);
      keypadPortControlR ^= (1<<keypad_R_0) | (1<<keypad_R_1) | (1<<keypad_R_2) | (1<<keypad_R_3);
      
      _delay_ms(50);
  
      // Store value for row
      int temp = keypadPortValueR;
      uint8_t keyPressCodeR = temp << 4;
  
      // Add value for column and row
      uint8_t keyPressCode = keyPressCodeC | keyPressCodeR;
      LCD4_Write_Float(keyPressCode);
  
      uint8_t blinkDuration = 0;
  
      // Comparison and resultant action
  
      // Column one

      if(keyPressCode == 0b11101110){
        LCD4_Write_String("a");
      }
      if(keyPressCode == 0b11011110){
        LCD4_Write_String("b");
      }
      if(keyPressCode == 0b10111110){
        LCD4_Write_String("c");
      }
      if(keyPressCode == 0b01111110){
        LCD4_Write_String("d");
      }
  
      // Column two
      if(keyPressCode == 0b11101101){
        LCD4_Write_String("e");
      }
      if(keyPressCode == 0b11011101){
        LCD4_Write_String("f");
      }
      if(keyPressCode == 0b10111101){
        LCD4_Write_String("g");;
      }
      if(keyPressCode == 0b01111101){
        LCD4_Write_String("h");
      }
  
      // Column three
      if(keyPressCode == 0b11101011){
        LCD4_Write_String("i");
      }
      if(keyPressCode == 0b11011011){
        LCD4_Write_String("j");;
      }
      if(keyPressCode == 0b10111011){
        LCD4_Write_String("k");
      }
      if(keyPressCode == 0b01111011){
        LCD4_Write_String("l");
      }
  
      // Column four
      if(keyPressCode == 0b11100111){
        LCD4_Write_String("m");
      }
      if(keyPressCode == 0b11010111){
        LCD4_Write_String("n");
      }
      if(keyPressCode == 0b10110111){
        LCD4_Write_String("o");
      }
      if(keyPressCode == 0b01110111){
        LCD4_Write_String("p");
      }
  
}*/
/*
// Function moving to a given position on the LCD screen
void lcd_gotoxy(unsigned char x, unsigned char y) {
  unsigned char firstCharAdr[] = {0x80, 0xC0, 0x94, 0xD4};
  lcdCommand(firstCharAdr[y - 1] + x - 1);
  _delay_ms(0.1);
}

void lcd_init(void) {
  lcdCommand(0x02); // To initialize LCD in 4-bit mode.
  _delay_ms(1);
  lcdCommand(0x28); // To initialize LCD in 2 lines, 5X7 dots and 4bit mode.
  _delay_ms(1);
  lcdCommand(0x01); // Clear LCD
  _delay_ms(1);
  lcdCommand(0x0E); // Turn on cursor ON
  _delay_ms(1);
  lcdCommand(0x80); // —8 go to first line and –0 is for 0th position
  _delay_ms(1);
  return;
}

void lcdCommand(char cmd_value) {
  char cmd_value1;
  cmd_value1 = cmd_value & 0xF0;          // Mask lower nibble
                                          // because PD4-PD7 pins are used.
  lcd_command(cmd_value1);                // Send to LCD
  cmd_value1 = ((cmd_value << 4) & 0xF0); // Shift 4-bit and mask
  lcd_command(cmd_value1);                // Send to LCD
}

void lcdData(char data_value) {
  char data_value1;
  data_value1 = data_value & 0xF0;          // Mask lower nibble
  lcd_data(data_value1);                    // because PD4-PD7 pins are used.
  data_value1 = ((data_value << 4) & 0xF0); // Shift 4-bit and mask
  lcd_data(data_value1);                    // Send to LCD
}

void lcd_command(unsigned char cmd) {
  ctrl = cmd;
  ctrl &= ~(1 << rs); // RS = 0 for command
  ctrl &= ~(1 << rw); // RW = 0 for write
  ctrl |= (1 << en);  // EN = 1 for High to Low pulse
  _delay_ms(1);
  ctrl &= ~(1 << en); // EN = 0 for High to Low pulse
  _delay_ms(40);
  return;
}

void lcd_data(unsigned char data) {
  ctrl = data;
  ctrl |= (1 << rs);  // RS = 1 for data
  ctrl &= ~(1 << rw); // RW = 0 for write
  ctrl |= (1 << en);  // EN = 1 for High to Low pulse
  _delay_ms(1);
  ctrl &= ~(1 << en); // EN = 0 for High to Low Pulse
  _delay_ms(40);
  return;
}

void lcd_print(
    unsigned char *str) { // store address value of the string in pointer *str
  int i = 0;
  while (str[i] !=
         '\0') {     // loop will go on till the NULL character in the string
    lcdData(str[i]); // sending data on LCD byte by byte
    i++;
  }
  return;
}
*/

