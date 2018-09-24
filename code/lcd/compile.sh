rm *.o *.hex *.elf
avr-gcc -g -Os -mmcu=atmega32 -c  lcd.c mq2.c main.c
avr-gcc -g -mmcu=atmega32 -o sen_dec.elf mq2.o lcd.o main.o
avr-objcopy -j .text -j .data -O ihex sen_dec.elf sen_dec.hex
avr-size --format=avr --mcu=atmega32 sen_dec.elf
avrdude -F -V -c stk500 -p m32 -P /dev/ttyUSB0 -b 115200 -U flash:w:sen_dec.hex
