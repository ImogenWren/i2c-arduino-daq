

/*
 I2C Pin Definition:

 
SDA -> A4 -> Green
SCL -> A5 -> Yellow


 */

#include <Arduino.h>
#include <Wire.h>


#include <autoDelay.h>
autoDelay printDelay;
#define PRINT_DELAY_S 6


#include "SCD41-CO2-sensor.h"
#include "STC31-CO2-sensor.h"
#include "SHT41-HT-sensor.h"
#include "ACS70331-current-sensor.h"


void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(100);
  }
  Serial.println("\nEuropean Project - i2c Sensor Interface");
  delay(1000);
  Wire.begin();
  scd41_Setup();
  stc31_Setup();
  sht41_Setup();

  // ACS70331_Setup();
}

//int countdown = 5;

bool sampleData = false;

void loop() {
  delay(1000);
  char printBuffer[64];  // all sensors share


  scd41_Data SCD41_data;
  char scd_tempBuffer[8];
  char humidBuffer[8];
  SCD41_data = scd41_Loop();  // This only updates data ~ every 5 seconds - now has global falg to identify when data has been updated

  stc31_Data STC31_data;
  char gasBuffer[8];
  char stc_tempBuffer[8];
 // STC31_data = stc31_Loop();

  sht41_Data SHT41_data;
  char sht_humidBuffer[8];
  char sht_tempBuffer[8];
  SHT41_data = sht41_Loop();





  if (scd41_DataReady) {  // only print data if sensor has new data
    sampleData = true;
  }

  if (printDelay.secondsDelay(PRINT_DELAY_S)) {
    if (sampleData) {
      dtostrf(SCD41_data.temperature, 4, 2, scd_tempBuffer);
      dtostrf(SCD41_data.humidity, 4, 2, humidBuffer);
      sprintf(printBuffer, "| SCD41: CO2: %4i ppm, Temperature: %s degC, Humidity: %s %% |", SCD41_data.CO2, scd_tempBuffer, humidBuffer);
      Serial.print(printBuffer);

      dtostrf(STC31_data.gasConcentration, 4, 2, gasBuffer);
      dtostrf(STC31_data.gasTemperature, 4, 2, stc_tempBuffer);
      sprintf(printBuffer, "| STC31: CO2: %s ppm, Temperature %s degC|", gasBuffer, stc_tempBuffer);
   ///   Serial.println(printBuffer);


      dtostrf(SHT41_data.temperature, 4, 2, sht_tempBuffer);
      dtostrf(SHT41_data.humidity, 4, 2, sht_humidBuffer);
      sprintf(printBuffer, "| SHT41: Temperature: %s degC, Humidity: %s %% |", sht_tempBuffer, sht_humidBuffer);
      Serial.println(printBuffer);


      //  countdown = 6;
      sampleData = false;
    }
  } else {
    // Just for debugging timings
    // Serial.print("Count: ");
    // Serial.println(countdown);
    //countdown--;
  }
}
