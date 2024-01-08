

/*
 I2C Pin Definition:

 
SDA -> A4 -> Green
SCL -> A5 -> Yellow


 */

#include <Arduino.h>
#include <SensirionI2CScd4x.h>
#include <Wire.h>


#include <autoDelay.h>

autoDelay sampleDelay;

#define SAMPLING_DELAY 100


#include "SCD41-CO2-sensor.h"




void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(100);
  }
  Wire.begin();
  scd41_Setup();
}



void loop() {
  scd41_Data SCD41_data;
  delay(100);
  // char co2Buffer[8];
  char tempBuffer[8];
  char humidBuffer[8];
  char printBuffer[128];
  SCD41_data = scd41_Loop();
  if (isDataReady) {            // only print data if it contains data
    //  dtostrf(SCD41_data.CO2 , 4, 2, co2Buffer);  // CO2 is not a float
    dtostrf(SCD41_data.temperature, 4, 2, tempBuffer);
    dtostrf(SCD41_data.humidity, 4, 2, humidBuffer);
    sprintf(printBuffer, "| SCD41: CO2: %4i, Temperature: %s, Humidity: %s |", SCD41_data.CO2, tempBuffer, humidBuffer);
    Serial.println(printBuffer);
  }
}
