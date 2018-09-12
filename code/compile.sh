avr-gcc -g -Os -mmcu=atmega8 -c led.c
avr-gcc -g -mmcu=atmega8 -o led.elf led.o
avr-objcopy -j .text -j .data -O ihex led.elf led.hex
avr-size --format=avr --mcu=atmega8 led.elf
avrdude -c avrispmkII -p m8 -U flash:w:led.hex
