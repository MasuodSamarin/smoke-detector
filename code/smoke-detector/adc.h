#ifndef MY_ADC_H_
#define MY_ADC_H_

#define ADC_OFFSET      (0.845)
//#define ADC_RAW_TO_MV   1

void ADC_init(void);
uint16_t ADC_read (uint8_t channel);


#endif
