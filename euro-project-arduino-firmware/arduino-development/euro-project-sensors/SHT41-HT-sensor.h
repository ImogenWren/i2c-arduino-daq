#include "SHTSensor.h"


// Note that all i2c devices sharing one bus must have distinct addresses. Thus
// this example only works with sensors that have distinct i2c addresses (e.g.
// SHT3x and SHT3x_alt, or SHT3x and SHTC3).
// Make sure not to use auto-detection as it will only pick up one sensor.

// Sensor with normal i2c address
// Sensor 1 with address pin pulled to GND
SHTSensor sht4x(SHTSensor::SHT4X);

// Sensor with alternative i2c address
// Sensor 2 with address pin pulled to Vdd
//SHTSensor sht2(SHTSensor::SHT3X_ALT);


struct sht41_Data {
  float humidity;
  float temperature;
};



void sht41_Setup() {
  Serial.println("\nSHT41 - Temp - Humidity - Sensor - Starting");

  // init on a specific sensor type (i.e. without auto detecting),
  // does not check if the sensor is responding and will thus always succeed.
  // initialize sensor with normal i2c-address
  sht4x.init();
}


sht41_Data sht41_Loop() {
  if (SHT41_ACTIVE) {
    sht41_Data SHT41_data;
    if (sht4x.readSample()) {
      //    Serial.print("SHT1 :\n");
      //    Serial.print("  RH: ");
      //    Serial.print(sht4x.getHumidity(), 2);
      //    Serial.print("\n");
      //    Serial.print("  T:  ");
      //    Serial.print(sht4x.getTemperature(), 2);
      //    Serial.print("\n");
      SHT41_data = { sht4x.getHumidity(), sht4x.getTemperature() };
      return SHT41_data;
    } else {
      Serial.print("SHT41: Error in readSample()\n");
      SHT41_ACTIVE = false;
      return;
    }
  }
}
