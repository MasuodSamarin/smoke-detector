#rm *.o *.hex *.elf *~
SRC="tim.c eeprom.c test.c menu.c adc.c lm35.c output.c keypad.c lcd.c mq2.c main.c"
OBJ="tim.o eeprom.o test.o menu.o adc.o lm35.o output.o keypad.o lcd.o mq2.o main.o"

avr-gcc -g -Os -mmcu=atmega32 -c $SRC
avr-gcc -g -mmcu=atmega32 -o smoke.elf $OBJ
avr-objcopy -j .text -j .data -O ihex smoke.elf smoke.hex
avr-size --format=avr --mcu=atmega32 smoke.elf

avrdude -F -V -c stk500 -p m32 -P /dev/ttyUSB0 -b 115200 -U flash:w:smoke.elf
#avrdude -F -V -c stk500 -p m32 -P /dev/ttyUSB0 -b 115200 -U eeprom:w:smoke.elf

rm *.o *.hex *.elf *~
