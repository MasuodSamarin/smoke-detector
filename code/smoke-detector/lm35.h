#ifndef LM35_H
#define LM35_H



#define LM35_ch1        1
#define LM35_ch2        2


#define temp_factor 4.8828125  // 5000 / 1023


float lm35_get_temp(void);
#endif
