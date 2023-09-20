

/*
 I2C Pin Definition:

 
SDA -> A4 -> Green
SCL -> A5 -> Yellow


 */

#include <Arduino.h>
#include <SensirionI2CScd4x.h>
#include <SensirionI2CStc3x.h>
#include <Wire.h>


//#include <autoDelay.h>
//autoDelay sampleDelay;
//#define SAMPLING_DELAY 100


#include "SCD41-CO2-sensor.h"
#include "STC31-CO2-sensor.h"
#include "ACS70331-current-sensor.h"


void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(100);
  }
  Wire.begin();
  scd41_Setup();
  stc31_Setup();
  ACS70331_Setup();
}



void loop() {
  delay(1000);
  char printBuffer[264];  // all sensors share


  scd41_Data SCD41_data;
  char scd_tempBuffer[8];
  char humidBuffer[8];
  SCD41_data = scd41_Loop();  // This only returns data ~ every 5 seconds

  stc31_Data STC31_data;
  char gasBuffer[8];
  char stc_tempBuffer[8];
  STC31_data = stc31_Loop();

  if (scd41_DataReady) {  // only print data if sensor has new data
    dtostrf(SCD41_data.temperature, 4, 2, scd_tempBuffer);
    dtostrf(SCD41_data.humidity, 4, 2, humidBuffer);
    sprintf(printBuffer, "| SCD41: CO2: %4i, Temperature: %s, Humidity: %s |", SCD41_data.CO2, scd_tempBuffer, humidBuffer);
    Serial.println(printBuffer);
  } else {
    dtostrf(STC31_data.gasConcentration, 4, 2, gasBuffer);
    dtostrf(STC31_data.gasTemperature, 4, 2, stc_tempBuffer);
    sprintf(printBuffer, "| STC31: Gas Concentration: %s, Temperature %s |", gasBuffer, stc_tempBuffer);
    Serial.println(printBuffer);
  }
}
