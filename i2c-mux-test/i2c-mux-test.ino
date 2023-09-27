/*
  Use the Qwiic Mux to access multiple I2C devices on seperate busses.
  By: Nathan Seidle @ SparkFun Electronics
  Date: May 17th, 2020
  License: This code is public domain but you buy me a beer if you use this
  and we meet someday (Beerware license).

  Some I2C devices respond to only one I2C address. This can be a problem
  when you want to hook multiple of a device to the I2C bus. An I2C Mux
  solves this issue by allowing you to change the 'channel' or port that
  the master is talking to.

  This example shows how to connect to different ports.
  The TCA9548A is a mux. This means when you enableMuxPort(2) then the SDA and SCL lines of the master (Arduino)
  are connected to port 2. Whatever I2C traffic you do, such as distanceSensor.startRanging() will be communicated to whatever
  sensor you have on port 2.

  Hardware Connections:
  Attach the Qwiic Mux Shield to your RedBoard or Uno.
  Plug a device into port 0 or 1
  Serial.print it out at 115200 baud to serial monitor.

  SparkFun labored with love to create this code. Feel like supporting open
  source? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14685
*/

#include <Wire.h>

#include <SparkFun_I2C_Mux_Arduino_Library.h>  //Click here to get the library: http://librarymanager/All#SparkFun_I2C_Mux
QWIICMUX myMux;


#include <autoDelay.h>
autoDelay printDelay;
#define PRINT_DELAY_S 6

// If Init as true, program will test sensor and if missing, will report then block action of sensor
bool SCD41_ACTIVE = true;
bool STC31_ACTIVE = true;
bool SHT41_ACTIVE = true;


#include "SCD41-CO2-sensor.h"

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Qwiic Mux Shield Read Example");
  delay(500);

  Wire.begin();


  if (myMux.begin() == false) {
    Serial.println("Mux not detected. Freezing...");
    while (1) {
      Serial.println("Here");
    }
  }
  Serial.println("Mux detected");

  delay(500);
  myMux.setPort(0);  //Connect master to port labeled '1' on the mux

  byte currentPortNumber = myMux.getPort();
  Serial.print("CurrentPort: ");
  Serial.println(currentPortNumber);
  delay(1000);
  Serial.println("Begin Sensor Setup");
//  myMux.enablePort(0);
  scd41_Setup();
}





void loop() {
  char printBuffer[64];  // all sensors share


  scd41_Data SCD41_data;
  char scd_tempBuffer[8];
  char humidBuffer[8];
  SCD41_data = scd41_Loop();  // This only updates data ~ every 5 seconds - now has global falg to identify when data has been updated

  if (printDelay.secondsDelay(PRINT_DELAY_S)) {
    //  if (sampleData) {

    if (SCD41_ACTIVE) {
      dtostrf(SCD41_data.temperature, 4, 2, scd_tempBuffer);
      dtostrf(SCD41_data.humidity, 4, 2, humidBuffer);
      //sprintf(printBuffer, "| SCD41: CO2: %4i ppm, Temperature: %s degC, Humidity: %s %% |", SCD41_data.CO2, scd_tempBuffer, humidBuffer);
      sprintf(printBuffer, "%4i, %s, %s,", SCD41_data.CO2, scd_tempBuffer, humidBuffer);
      Serial.print(printBuffer);
    }
    Serial.println();
  } else {

  }
}




void i2c_scanner() {
  Serial.println();

  byte nDevices = 0;
  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 0x10) {
        Serial.print("0");
      }
      Serial.print(address, HEX);
      Serial.println();

      nDevices++;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 0x10) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }

  if (nDevices == 0) {
    Serial.println("No I2C devices found");
  } else {
    Serial.println("Done");
  }

  delay(1000);
}