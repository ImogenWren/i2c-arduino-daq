

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
  delay(100);
  scd41_Loop();
}
