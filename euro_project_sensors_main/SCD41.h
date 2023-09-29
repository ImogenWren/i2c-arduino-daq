/* # Sensirion SCD41 - CO2 Sensor - i2c

- 5v or 3.3v (calibrated for 3.3v)

 - Pinout: ** Double Check

 	- SDA:   Yellow
	- GND: 	  black
  - Vdd:    Red
	- SCL:   green

 */


#ifndef SCD41_h
#define SCD41_h


#include <SensirionI2CScd4x.h>



class SCD41 {
public:

  SensirionI2CScd4x scd4x;


  // This is a little redundant as object can be queried directly
  // Could be used to make a single function to return variables?
  // leaving as so for now
  struct scd41_Data {
    uint16_t CO2;
    float temperature;
    float humidity;
  };

  // Constructor
  SCD41() {
  }

  void scd41_Setup();



  scd41_Data scd41_Loop();  // This does return data but now its inside class can just access object globals directly



// Not needed as these are passed using the data structure
  //uint16_t CO2;
  //float temperature;
  //float humidity;

  bool scd41_DataReady = false;  // Global flag to id data ready

private:
};

#endif