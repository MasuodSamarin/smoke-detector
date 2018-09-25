#rm *.o *.hex *.elf *~

avr-gcc -g -Os -mmcu=atmega32 -c  adc.c lm35.c output.c keypad.c lcd.c mq2.c main.c
avr-gcc -g -mmcu=atmega32 -o smoke.elf adc.o lm35.o output.o keypad.o lcd.o mq2.o main.o
avr-objcopy -j .text -j .data -O ihex smoke.elf smoke.hex
avr-size --format=avr --mcu=atmega32 smoke.elf

avrdude -F -V -c stk500 -p m32 -P /dev/ttyUSB0 -b 115200 -U flash:w:smoke.hex

rm *.o *.hex *.elf *~
