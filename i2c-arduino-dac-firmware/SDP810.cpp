/* # Sensirion SDP810 - Differential Pressure Sensor - i2c

- 5v or 3.3v 

 - Pinout: 
                  Sensor housing (back)
                  ______________________________
                  |  ________________________   |
                  | |                         | | 
                  | |   4     3     2     1   | |
                  | | [sda] [gnd] [vdd] [scl] | |
                  |_|_________________________|_|

 	- SDA:   Black
	- GND: 	 Red
  - Vdd:   White
	- SCL:   Yellow

 */

#include "SDP810.h"

#define DEBUG_SDP810 false


void SDP810::sdp810_Setup() {
  // Serial.println("SDP810 - Differential Pressure (dP) - Sensor - Starting");
  uint16_t error;

  sdp.begin(Wire, SDP8XX_I2C_ADDRESS_0);

  uint32_t productNumber;
  uint8_t serialNumber[8];
  uint8_t serialNumberSize = 8;

  sdp.stopContinuousMeasurement();

  error = sdp.readProductIdentifier(productNumber, serialNumber,
                                    serialNumberSize);

#if DEBUG_SDP810 == true
  if (error) {
    Serial.print(ID);
    // Serial.println(F(": Error Reading Product ID"));
    char errorMessage[64];
    //Serial.print("Error trying to execute readProductIdentifier(): ");
    errorToString(error, errorMessage, 64);
    Serial.println(errorMessage);
  } else {
    //Serial.print("ProductNumber:");
    //Serial.print(productNumber);
    //Serial.print("\t");
    //Serial.print("SerialNumber:");
    //Serial.print("0x");
    //for (size_t i = 0; i < serialNumberSize; i++) {
    //  Serial.print(serialNumber[i], HEX);
    // }
    //Serial.println();
  }
#endif

  error = sdp.startContinuousMeasurementWithDiffPressureTCompAndAveraging();

  if (error) {
#if DEBUG_SDP810 == true
    Serial.print(ID);
    char errorMessage[64];
    //Serial.println(F(": Error Starting Measurement"));
    //   Serial.print(
    //     "Error trying to execute "
    //    "startContinuousMeasurementWithDiffPressureTCompAndAveraging(): ");
    errorToString(error, errorMessage, 64);
    Serial.println(errorMessage);
#endif
  }
}



SDP810::sdp810_Data SDP810::sdp810_Loop() {
  sdp810_Data SDP810_data;

  uint16_t error;


  // Read Measurement local variables will be passed to global hidden inside class
  float differentialPressure;
  float temperature;

  error = sdp.readMeasurement(differentialPressure, temperature);

  if (error) {
#if DEBUG_SDP810 == true
    Serial.print(ID);
    Serial.print(F(": "));
    Serial.print(error);
    Serial.print(F(", "));
    // Serial.println(F(": Error trying to execute readMeasurement(): "));
    char errorMessage[64];
    errorToString(error, errorMessage, 64);
    Serial.println(errorMessage);
#endif
    SDP810_data = { 0, 0 };
  } else {
    //Serial.print("DifferentialPressure[Pa]:");
    //Serial.print(differentialPressure);
    //Serial.print("\t");
    //Serial.print("Temperature[°C]:");
    //Serial.print(temperature);
    //Serial.println();
    SDP810_data = { differentialPressure, temperature };
  }
  return SDP810_data;
}





// Comment for auto format
