#ifndef F_CPU
#define F_CPU 8000000UL // or whatever may be your frequency
#endif


#include <avr/io.h>
#include <util/delay.h>                // for _delay_ms()
#include "adc.h"
#include "mq2.h"


float ResistanceCalculation(int raw_adc)
{ // sensor and load resistor forms a voltage divider. so using analog value and load value 
  return ( ((float)RL_VALUE*(1023-raw_adc)/raw_adc));     // we will find sensor resistor.
}
 

float SensorCalibration(void)
{
  int i;                                   // This function assumes that sensor is in clean air.
  float val=0;
  const int factor = 50;
  
  for (i=0;i<factor;i++) {                   //take multiple samples and calculate the average value
	  
    val += ResistanceCalculation(ADC_read(0));
    _delay_ms(100);
  }
  val = val/factor;                  
  val = val/RO_CLEAN_AIR_FACTOR;                        //divided by RO_CLEAN_AIR_FACTOR yields the Ro 
                                                        //according to the chart in the datasheet 
 
  return val; 
}

 
float ReadSensor()
{
  int i;
  float rs=0;
 
  for (i=0;i<5;i++) {                                 // take multiple readings and average it.
    rs += ResistanceCalculation(ADC_read(0));   // rs changes according to gas concentration.
    _delay_ms(100);
  }
 
  rs = rs/5;
 
  return rs;  
}
 

int GetGasPercentage(float rs_ro_ratio, int gas_id)
{
  if ( gas_id == LPG ) {
     return GetPercentage(rs_ro_ratio,LPGCurve);
   
  } else if ( gas_id == SMOKE ) {
     return GetPercentage(rs_ro_ratio,SmokeCurve);
  }    
 
  return 0;
}
 
 
int  GetPercentage(float rs_ro_ratio, float *curve)
{ //Using slope,ratio(y2) and another point(x1,y1) on line we will find  
  return (pow(10,( ((log(rs_ro_ratio)-curve[1])/curve[2]) + curve[0])));   // gas concentration(x2) using x2 = [((y2-y1)/slope)+x1]
  // as in curves are on logarithmic coordinate, power of 10 is taken to convert result to non-logarithmic. 
}
