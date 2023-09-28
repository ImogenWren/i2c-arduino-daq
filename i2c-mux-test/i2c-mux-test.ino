/* # European Project i2c Sensor Mux


List of Sensors and Mux Channel Numbers
Mux 0 = i2c bus from nano
Mux 1 = Mux Module 1
Mux 2 = Mux Module 2 (for later expansion if required)
 
|No. |Sensor Name (system)  |	Sensor Type (model) |	Data Returned       |	Units                 |	Sample Rate  (Hz or every X seconds)| Mux/Channel  |
|--- |---                   |---                  |---                  |---                    |---                                  |---           |
| 1  | CD1                  | SEK-SCD41 - CO2     | CO2, Temp, Humidity | ppm/fraction, degC, % | 5 s                                 |  1.0         |
| 2  | CD2                  | SEK-SCD41 - CO2     | CO2, Temp, Humidity | ppm/fraction, degC, % | 5 s                                 |  1.1         |
| 3  | CD3                  | SEK-STC31 - CO2     | CO2                 | ppm/fraction          | 2 s  (Can work with 4s to match RHT)|  1.0         |
| 4  | CD4                  | SEK-STC31 - CO2     | CO2                 | ppm/fraction          | 2 s  (Can work with 4s to match RHT)|  1.1         |
| 5  | CD5                  | SEK-STC31 - CO2     | CO2                 | ppm/fraction          | 2 s  (Can work with 4s to match RHT)|  1.2         |
| 6  | CD6                  | SEK-STC31 - CO2     | CO2                 | ppm/fraction          | 2 s  (Can work with 4s to match RHT)|  1.3         |
| 7  | RHT3                 | SEK-SHT41I-AD1B     | Temp, Humidity      | degC, %               | 4 s                                 |  1.4         |
| 8  | RHT4                 | SEK-SHT41I-AD1B     | Temp, Humidity      | degC, %               | 4 s                                 |  1.5         |
| 9  | RHT5                 | SEK-SHT41I-AD1B     | Temp, Humidity      | degC, %               | 4 s                                 |  1.6         |
| 10 | RHT6                 | SEK-SHT41I-AD1B     | Temp, Humidity      | degC, %               | 4 s                                 |  1.7         |
| 11 | Mux 1                | I2C MUX 3 click     | i2C Mux             | n/a                   | n/a                                 |  0.0         |
| 12 | Mux 2                | I2C MUX 3 click     | i2C Mux             | n/a                   | n/a                                 |  0.1  (change address)|




*/

#include <Wire.h>


#include <SparkFun_I2C_Mux_Arduino_Library.h>  //Click here to get the library: http://librarymanager/All#SparkFun_I2C_Mux
QWIICMUX senseMux;

// Maybe Correct?
//#include <ClosedCube_TCA9548A.h>
//#define TCA9548A_I2C_ADDRESS 0x70

//ClosedCube::Wired::TCA9548A tca9548a;


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
  Serial.println("\nSensor i2c Mux");
  delay(500);

  Wire.begin();


   if (myMux.begin(0x70, Wire) == false) {
    Serial.println("Mux not detected. Freezing...");
    while (1) {
       Serial.println("Here");
     }
   }
   Serial.println("Mux detected");

  delay(500);

   myMux.setPort(0);  //Connect master to port labeled '1' on the mux OR 0?


//  uint8_t returnCode = tca9548a.selectChannel(1);
//  if (returnCode == 0) {
//    Serial.println("i2c Device Found");
 // } else {
 //   Serial.print("Error scan channel (Code:");
  //  Serial.print(returnCode);
 //   Serial.println(")");
 // }


  byte currentChannel = myMux.getPort();
//uint8_t currentChannel = tca9548a.getChannel();

  Serial.print("CurrentChannel: ");
  Serial.println(currentChannel);
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