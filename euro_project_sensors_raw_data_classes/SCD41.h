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


  struct scd41_Data {
    uint16_t CO2;
    float temperature;
    float humidity;
  };

  // COnstructor
  SCD41() {
  }

  void scd41_Setup();

  scd41_Data scd41_Loop();

  // scd41_Data SCD41_data; // making this global so this function can just update the global variable every time new data is available.
  scd41_Data scd41_data;

  int16_t CO2;
  float temperature;
  float humdity;

  bool scd41_DataReady = false;  // Dont like as global but quick fix better now hidden in class. simplify names

private:
};

#endif