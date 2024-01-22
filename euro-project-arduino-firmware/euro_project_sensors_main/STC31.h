/* # Sensirion SEK-STC31 - CO2 Sensor - i2c

- 5v or 3.3v (calibrated for 3.3v)

 - Pinout:
 
	- Vdd:    green
	- SCL:    brown
	- GND: 	  pink
	- SDA:   Yellow
 */


#ifndef STC31_h
#define STC31_h



#include <SensirionI2CStc3x.h>


class STC31 {
public:

  SensirionI2CStc3x stc3x;


  struct stc31_Data {
    float gasConcentration;
    float gasTemperature;
  };



  void stc31_Setup();

  stc31_Data stc31_Loop();  // This does return data but now its inside class can just access object globals directly




private:
};














#endif