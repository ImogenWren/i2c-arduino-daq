/* # Sensirion SHT41 - Temp - Humidity Sensor - i2c

- 5v or 3.3v (calibrated for 3.3v)

 - Pinout: (for Ethernet) Double Check

 	- SDA:   Yellow
	- GND: 	  black
  - Vdd:    Red
	- SCL:   green

 */



#ifndef SHT41_h
#define SHT41_h

#include "SHTSensor.h"
#include <Arduino.h>



class SHT41 {
public:
  // Note that all i2c devices sharing one bus must have distinct addresses. Thus
  // this example only works with sensors that have distinct i2c addresses (e.g.
  // SHT3x and SHT3x_alt, or SHT3x and SHTC3).
  // Make sure not to use auto-detection as it will only pick up one sensor.

  // Sensor with normal i2c address
  // Sensor 1 with address pin pulled to GND
  //  SHTSensor sht4x(SHTSensor::SHT4X); // DOES NOT WORK - DONT KNOW WHY
  SHTSensor sht4x{ SHTSensor::SHT4X };  // Doesnt Work inside class UNLESS CURLY BRACES - WHY WHO KNOWS!?!?!?!?!?!?!??!?!

  struct sht41_Data {
    float humidity;
    float temperature;
  };

  // Constructor
  SHT41() {
    // SHTSensor sht4x(SHTSensor::SHT4X);
  }


  void sht41_Setup();


  sht41_Data sht41_Loop();



private:
};




#endif
