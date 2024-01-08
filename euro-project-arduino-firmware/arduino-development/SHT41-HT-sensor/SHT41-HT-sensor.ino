


#include <Wire.h>
#include "SHT41-HT-sensor.h"




void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200);
  delay(1000);  // let serial console settle
  sht41_Setup();
}

void loop() {
  char printBuffer[64];

  sht41_Data SHT41_data;
  char sht_humidBuffer[8];
  char sht_tempBuffer[8];
  SHT41_data = sht41_Loop();

  dtostrf(SHT41_data.temperature, 4, 2, sht_tempBuffer);
  dtostrf(SHT41_data.humidity, 4, 2, sht_humidBuffer);
  sprintf(printBuffer, "| SHT41: Temperature: %s degC, Humidity: %s %% |", sht_tempBuffer, sht_humidBuffer);
  Serial.println(printBuffer);


  delay(1000);
}
