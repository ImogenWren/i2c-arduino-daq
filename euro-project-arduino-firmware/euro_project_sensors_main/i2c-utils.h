

#include <SparkFun_I2C_Mux_Arduino_Library.h>  //Click here to get the library: http://librarymanager/All#SparkFun_I2C_Mux

QWIICMUX sensorMux;   // Create instance of i2c mux


void setupMux() {
  Wire.begin();
  if (sensorMux.begin(0x70, Wire) == false) {
    Serial.println("Mux not detected. Freezing...");
    while (1) {
      Serial.println("Please Reset Arduino");
    }
  }
 // Serial.println("Mux detected");
  delay(500);
}



void checkMuxPort(){
  byte currentChannel = sensorMux.getPort();
//  Serial.print("CurrentChannel: ");
//  Serial.println(currentChannel);
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