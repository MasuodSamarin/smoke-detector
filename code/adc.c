#ifndef F_CPU
#define F_CPU 8000000UL // or whatever may be your frequency
#endif


#include <avr/io.h>
#include <util/delay.h>                // for _delay_ms()
#include "adc.h"


void ADC_init (void)
{
	ADMUX = 0x00;
	ADMUX &= ~(1<<ADLAR);
	ADMUX |=(1<<REFS0)|(1<<REFS1);
	ADCSRA = 0x00;
	ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(0<<ADPS0);
}

void ADC_start (void)
{
	ADCSRA |= (1<<ADSC);
}

uint16_t ADC_read (uint8_t channel)
{
	ADMUX &= 0b01100000;
	ADMUX |=channel;
	
	ADC_start();
	
	uint16_t value = 0;
	while (!(ADCSRA&(1<<ADIF)));
	value = ADCL;
	value += (ADCH<<8);
	return value;
}



