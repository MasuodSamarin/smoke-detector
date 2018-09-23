f_name="mq2"
avr-gcc -g -Os -mmcu=atmega8 -c "$f_name.c"
avr-gcc -g -mmcu=atmega8 -o "$f_name.elf" "$f_name.o"
avr-objcopy -j .text -j .data -O ihex "$f_name.elf" "$f_name.hex"
avr-size --format=avr --mcu=atmega8 "$f_name.hex"
avrdude -c avrispmkII -p m8 -U flash:w:"$f_name.hex"
