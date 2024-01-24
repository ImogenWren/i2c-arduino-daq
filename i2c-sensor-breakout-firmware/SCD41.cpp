/* # Sensirion SCD41 - CO2 Sensor - i2c

- 5v or 3.3v (calibrated for 3.3v)

 - Pinout: ** Double Check

 	- SDA:   Yellow
	- GND: 	  black
  - Vdd:    Red
	- SCL:   green

 */
 


#include "SCD41.h"

void SCD41::scd41_Setup() {
  // Serial.println("\nSCD41 - CO2 - Temp - Humidity Sensor - Starting");

  uint16_t error;
  // char errorMessage[128];

  scd4x.begin(Wire);

  // stop potentially previously started measurement
  error = scd4x.stopPeriodicMeasurement();
  if (error) {
   // Serial.println("SCD41: Error executing stopPeriodicMeasurement(): ");
    //errorToString(error, errorMessage, 256);
    //  Serial.println(errorMessage);
  }

  uint16_t serial0;
  uint16_t serial1;
  uint16_t serial2;
  error = scd4x.getSerialNumber(serial0, serial1, serial2);
  if (error) {
  //  Serial.println("SCD41: Error executing getSerialNumber(): ");
    // SCD41_ACTIVE = false;
    //  errorToString(error, errorMessage, 256);
    //  Serial.println(errorMessage);
  } else {
    //   printSerialNumber(serial0, serial1, serial2);
  }

  // Start Measurement
  error = scd4x.startPeriodicMeasurement();
  if (error) {
  //  Serial.println("SCD41: Error executing startPeriodicMeasurement(): ");
    //  errorToString(error, errorMessage, 256);
    // Serial.println(errorMessage);
  }

  //  Serial.println("SCD41: Waiting for first measurement... (5 sec)");
}



SCD41::scd41_Data SCD41::scd41_Loop() {

 scd41_Data scd41_data;
  uint16_t error;
  // char errorMessage[64];

  // Read Measurement - local variables will be passed to global hidden inside class
  uint16_t co2_l = 0;
  float temperature_l = 0.0f;
  float humidity_l = 0.0f;
// 

  scd41_DataReady = false;
  error = scd4x.getDataReadyFlag(scd41_DataReady);
  if (error) {
   // Serial.println("SCD41: Error executing getDataReadyFlag(): ");
    // errorToString(error, errorMessage, 128);
    // Serial.println(errorMessage);
    scd41_data = { 0, 0, 0 };
    return scd41_data;
  }
  if (!scd41_DataReady) {
    return scd41_data;
  }
  error = scd4x.readMeasurement(co2_l, temperature_l, humidity_l);
  if (error) {
    Serial.println("SCD41: Error executing readMeasurement(): ");
    //   errorToString(error, errorMessage, 256);
    //   Serial.println(errorMessage);
    scd41_data = { 0, 0, 0 };
    return scd41_data;
  } else if (co2_l == 0) {
    Serial.println("SCD41: Invalid sample detected, skipping.");
    scd41_data = { 0, 0, 0 };
    return scd41_data;
  } else {
    // Return the data to global variables
    scd41_data = { co2_l, temperature_l, humidity_l };    
  }
  return scd41_data;
}