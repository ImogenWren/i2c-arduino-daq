

#include <Arduino.h>
#include <SensirionI2CStc3x.h>
#include <Wire.h>
#include <inttypes.h>

#include "STC31-CO2-sensor.h"



void setup() {

  Serial.begin(115200);
  while (!Serial) {
    delay(100);
  }

  Wire.begin();
  stc31_Setup();
}

void loop() {
  stc31_Data STC31_data;
  delay(1000);
  char gasBuffer[8];
  char tempBuffer[8];
  char printBuffer[128];
  STC31_data = stc31_Loop();
  dtostrf(STC31_data.gasConcentration, 4, 2, gasBuffer);
  dtostrf(STC31_data.gasTemperature, 4, 2, tempBuffer);
  sprintf(printBuffer, "| STC31: Gas Concentration: %s, Temperature %s |", gasBuffer, tempBuffer);
  Serial.println(printBuffer);
}
