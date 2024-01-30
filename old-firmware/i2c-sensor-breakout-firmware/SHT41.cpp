/* # Sensirion SHT41 - Temp - Humidity Sensor - i2c

- 5v or 3.3v (calibrated for 3.3v)

 - Pinout: (for Ethernet) Double Check

 	- SDA:   Yellow
	- GND: 	  black
  - Vdd:    Red
	- SCL:   green

 */


#include "SHT41.h"



void SHT41::sht41_Setup() {
  // Serial.println("\nSHT41 - Temp - Humidity - Sensor - Starting");

  // init on a specific sensor type (i.e. without auto detecting),
  // does not check if the sensor is responding and will thus always succeed.
  // initialize sensor with normal i2c-address
  sht4x.init();
}



SHT41::sht41_Data SHT41::sht41_Loop() {
  sht41_Data SHT41_data;
  if (sht4x.readSample()) {
   // Serial.begin(115200);
   // Serial.print("SHT1 :\n");
   // Serial.print("  RH: ");
   // Serial.print(sht4x.getHumidity(), 2);
  ///  Serial.print("\n");
  //  Serial.print("  T:  ");
  //  Serial.print(sht4x.getTemperature(), 2);
  //  Serial.print("\n");
    SHT41_data = { sht4x.getHumidity(), sht4x.getTemperature() };
  } else {
    // Serial.print("SHT41: Error in readSample()\n");
    //  SHT41_ACTIVE = false;
    SHT41_data = { 0, 0 };
  }
  return SHT41_data;
}
