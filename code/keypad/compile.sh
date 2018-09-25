rm *.hex *.o *.elf
avr-gcc -g -Os -mmcu=atmega32 -c main.c lcd.c
avr-gcc -g -mmcu=atmega32 -o key.elf main.o lcd.o
avr-objcopy -j .text -j .data -O ihex key.elf key.hex
avr-size --format=avr --mcu=atmega32 key.elf
avrdude -c stk500 -p m32 -P /dev/ttyUSB0 -U flash:w:key.hex
