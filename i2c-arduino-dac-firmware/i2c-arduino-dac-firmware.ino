/* # European Project i2c Sensor Mux - MAIN


List of Sensors and Mux Channel Numbers
Mux 0 = i2c bus from nano
Mux 1 = Mux Module 1
Mux 2 = Mux Module 2 (for later expansion if required)
 
|No. |Sensor Name (system)  |	Sensor Type (model) |	Data Returned       |	Units                 |	Sample Rate  (Hz or every X seconds)| Mux.Channel  |
|--- |---                   |---                  |---                  |---                    |---                                  |---           |
| 1  | CD1                  | SEK-SCD41 - CO2     | CO2, Temp, Humidity | ppm/fraction, degC, % | 5 s                                 |  1.0         |
| 2  | CD2                  | SEK-SCD41 - CO2     | CO2, Temp, Humidity | ppm/fraction, degC, % | 5 s                                 |  1.1         |
| 3  | CD3                  | SEK-STC31 - CO2     | CO2                 | ppm/fraction          | 2 s  (Can work with 4s to match RHT)|  1.4         |  These might need to move channels
| 4  | CD4                  | SEK-STC31 - CO2     | CO2                 | ppm/fraction          | 2 s  (Can work with 4s to match RHT)|  1.5         |
| 5  | CD5                  | SEK-STC31 - CO2     | CO2                 | ppm/fraction          | 2 s  (Can work with 4s to match RHT)|  1.2         |
| 6  | CD6                  | SEK-STC31 - CO2     | CO2                 | ppm/fraction          | 2 s  (Can work with 4s to match RHT)|  1.3         |
| 7  | RHT3                 | SEK-SHT41I-AD1B     | Temp, Humidity      | degC, %               | 4 s                                 |  1.0         |
| 8  | RHT4                 | SEK-SHT41I-AD1B     | Temp, Humidity      | degC, %               | 4 s                                 |  1.1         |
| 9  | RHT5                 | SEK-SHT41I-AD1B     | Temp, Humidity      | degC, %               | 4 s                                 |  1.2         |
| 10 | RHT6                 | SEK-SHT41I-AD1B     | Temp, Humidity      | degC, %               | 4 s                                 |  1.3         |
| 11 | dP1                  | SDP810-125Pa        | diffPressure, Temp  | mBar, degC            | n/a                                 |  1.5         |
| 12 | dP2                  | SDP810-500Pa        | diffPressure, Temp  | mBar, degC            | n/a                                 |  1.6         |
| 13 | dP3                  | SDP810-500Pa        | diffPressure, Temp  | mBar, degC            | n/a                                 |  1.7         |
| 14 | Mux 1                | I2C MUX 3 click     | i2C Mux             | n/a                   | n/a                                 |  0.0         |
| 15 | Mux 2                | I2C MUX 3 click     | i2C Mux             | n/a                   | n/a                                 |  0.1  (change address)|


NOTES:
  - Issues found with SCD41 and STC31 operating on the same channel.
    - Moving Channels to Mitigate
    - Did not change anything
    - Changed power source to 3v3
    - Problem solved? For now! [x]


*/


// define the active sensors
bool CD1_ACTIVE = 1;
bool CD2_ACTIVE = 1;
bool CD3_ACTIVE = 1;
bool CD4_ACTIVE = 1;
bool CD5_ACTIVE = 1;
bool CD6_ACTIVE = 1;
bool RHT3_ACTIVE = 1;
bool RHT4_ACTIVE = 1;
bool RHT5_ACTIVE = 1;
bool RHT6_ACTIVE = 1;
bool dP1_ACTIVE = 1;
bool dP2_ACTIVE = 1;
bool dP3_ACTIVE = 1;




#include <Wire.h>
#include "i2c-utils.h"
#include "UI-utils.h"


#include <autoDelay.h>
autoDelay printDelay;
#define PRINT_DELAY_S 3


#define DEBUG true

// Create instances for each sensor
#include "SCD41.h"
SCD41 CD1("CD1");  // Create instance of SCD41 for CD1
SCD41 CD2("CD2");  // Create instance of SCD41 for CD2

#include "STC31.h"
STC31 CD3("CD3");  // Create instance of STC31 for CD3
STC31 CD4("CD4");  // Create instance of STC31 for CD4
STC31 CD5("CD5");  // Create instance of STC31 for CD5
STC31 CD6("CD6");  // Create instance of STC31 for CD6

#include "SHT41.h"
SHT41 RHT3("RHT3");  // Create instance of SHT41 for RHT3
SHT41 RHT4("RHT4");  // Create instance of SHT41 for RHT4
SHT41 RHT5("RHT5");  // Create instance of SHT41 for RHT5
SHT41 RHT6("RHT6");  // Create instance of SHT41 for RHT6

#include "SDP810.h"
SDP810 dP1("dP1");  // Create instance of SDP810 for dP1
SDP810 dP2("dP2");  // Create instance of SDP810 for dP2
SDP810 dP3("dP3");  // Create instance of SDP810 for dP3



void setup() {
  Serial.begin(19200);
  // Serial.println(F("\nSensor i2c Mux"));
  delay(50);
  setupMux();
  delay(40);
  // Serial.println("Begin Sensor Setup");

  // sensorMux.setPort(0); // Make sure this is set to the port you wish to scan
  //i2c_scanner(); // Use this section to find attached sensors
  // while (1){}

  sensorMux.setPort(0);  // Ensure that sensors with the same ID are not connected to the same port
  if (CD1_ACTIVE) { CD1.scd41_Setup(); }
  if (RHT3_ACTIVE) { RHT3.sht41_Setup(); }
  delay(40);

  sensorMux.setPort(1);  //
  if (CD2_ACTIVE) { CD2.scd41_Setup(); }
  if (RHT4_ACTIVE) { RHT4.sht41_Setup(); }
  delay(40);

  sensorMux.setPort(2);
  if (CD5_ACTIVE) { CD5.stc31_Setup(); }
  if (RHT5_ACTIVE) { RHT5.sht41_Setup(); }
  delay(40);

  sensorMux.setPort(3);
  if (CD6_ACTIVE) { CD6.stc31_Setup(); }
  if (RHT6_ACTIVE) { RHT6.sht41_Setup(); }
  delay(40);

  sensorMux.setPort(4);
  if (CD3_ACTIVE) { CD3.stc31_Setup(); }
  delay(40);
  sensorMux.setPort(5);
  if (CD4_ACTIVE) { CD4.stc31_Setup(); }
  if (dP1_ACTIVE) { dP1.sdp810_Setup(); }
  delay(40);

  sensorMux.setPort(6);
  if (dP2_ACTIVE) { dP2.sdp810_Setup(); }
  delay(40);

  sensorMux.setPort(7);
  if (dP3_ACTIVE) { dP3.sdp810_Setup(); }
  delay(40);

  // Unused Ports
  // printDataHeader();  // Data header tells user order of data returned via serial

  delay(100);
}



uint16_t numSamples = 0;

void loop() {

  if (printDelay.secondsDelay(PRINT_DELAY_S)) {  // now sensor sampling also happens at the slower rate of printDelay
    // Set up variables to gather all sensor data
    SCD41::scd41_Data CD1_data;  // Return types for SCD data
    SCD41::scd41_Data CD2_data;  // Return types for SCD data

    STC31::stc31_Data CD3_data;  // Return types for STC Data
    STC31::stc31_Data CD4_data;  // Return types for STC Data
    STC31::stc31_Data CD5_data;  // Return types for STC Data
    STC31::stc31_Data CD6_data;  // Return types for STC Data

    SHT41::sht41_Data RHT3_data;  // Return types for SHT Data
    SHT41::sht41_Data RHT4_data;  // Return types for SHT Data
    SHT41::sht41_Data RHT5_data;  // Return types for SHT Data
    SHT41::sht41_Data RHT6_data;  // Return types for SHT Data

    SDP810::sdp810_Data dP1_data;  // return types for SDP810 data
    SDP810::sdp810_Data dP2_data;  // return types for SDP810 data
    SDP810::sdp810_Data dP3_data;  // return types for SDP810 data


    // Data gathering methods
    // USER NOTE: change order here to set port for each sensor

    delay(10);
    sensorMux.setPort(0);  //  Change port address to 0 and read all sensors on 0
    delay(10);
    if (CD1_ACTIVE) { CD1_data = CD1.scd41_Loop(); }     // This only updates data ~ every 5 seconds
    if (RHT3_ACTIVE) { RHT3_data = RHT3.sht41_Loop(); }  //

    delay(10);
    sensorMux.setPort(1);  //  Change port address to 1 and read all sensors on 1
    delay(10);
    if (CD2_ACTIVE) { CD2_data = CD2.scd41_Loop(); }     // This only updates data ~ every 5 seconds
    if (RHT4_ACTIVE) { RHT4_data = RHT4.sht41_Loop(); }  //

    delay(10);
    sensorMux.setPort(2);  //  Change port address to 1 and read all sensors on 2
    delay(10);
    if (CD5_ACTIVE) { CD5_data = CD5.stc31_Loop(); }     //
    if (RHT5_ACTIVE) { RHT5_data = RHT5.sht41_Loop(); }  //

    delay(10);
    sensorMux.setPort(3);  //  Change port address to 1 and read all sensors on 3
    delay(10);
    if (CD6_ACTIVE) { CD6_data = CD6.stc31_Loop(); }     //
    if (RHT6_ACTIVE) { RHT6_data = RHT6.sht41_Loop(); }  //

    delay(10);
    sensorMux.setPort(4);
    delay(10);
    if (CD3_ACTIVE) { CD3_data = CD3.stc31_Loop(); }  //

    delay(10);
    sensorMux.setPort(5);
    delay(10);
    if (CD4_ACTIVE) { CD4_data = CD4.stc31_Loop(); }  //
    if (dP1_ACTIVE) { dP1_data = dP1.sdp810_Loop(); }

    delay(10);
    sensorMux.setPort(6);
    delay(10);
    if (dP2_ACTIVE) { dP2_data = dP2.sdp810_Loop(); }

    delay(10);
    sensorMux.setPort(7);
    delay(10);
    if (dP3_ACTIVE) { dP3_data = dP3.sdp810_Loop(); }

    // Unused Ports

    // Printing/transmitting data to serial output
    // if (printDelay.secondsDelay(PRINT_DELAY_S)) {   // moved this to also delay the sensor readings
    char printBuffer[32];  // all sensors share single print buffer

    if (numSamples < 0) {
      //skip printing the 0 sample for stability (disabled for now)
    } else {
      sprintf(printBuffer, "%03i:  ", numSamples);  // Print number of samples taken for tracking function (remove line if unneeded)
      Serial.print(printBuffer);

      if (CD1_ACTIVE) {
        char scd_tempBuffer[6];
        char scd_humidBuffer[6];
        dtostrf(CD1_data.temperature, 4, 2, scd_tempBuffer);
        dtostrf(CD1_data.humidity, 4, 2, scd_humidBuffer);
        //sprintf(printBuffer, "| SCD41: CO2: %4i ppm, Temperature: %s degC, Humidity: %s %% |", CD1_data.CO2, scd_tempBuffer, scd_humidBuffer);
        sprintf(printBuffer, "%s: %4i, %5s, %5s, ", CD1.ID, CD1_data.CO2, scd_tempBuffer, scd_humidBuffer);  // Just the Data
        Serial.print(printBuffer);
      }
      if (CD2_ACTIVE) {
        char scd_tempBuffer[6];
        char scd_humidBuffer[6];
        dtostrf(CD2_data.temperature, 4, 2, scd_tempBuffer);
        dtostrf(CD2_data.humidity, 4, 2, scd_humidBuffer);
        sprintf(printBuffer, "%s: %4i, %5s, %5s, ", CD2.ID, CD2_data.CO2, scd_tempBuffer, scd_humidBuffer);  // Just the Data
        Serial.print(printBuffer);
      }

      if (CD3_ACTIVE) {
        char stc_gasBuffer[6];
        char stc_tempBuffer[6];
        dtostrf(CD3_data.gasConcentration, 4, 2, stc_gasBuffer);
        dtostrf(CD3_data.gasTemperature, 4, 2, stc_tempBuffer);
        //sprintf(printBuffer, "| STC31: CO2: %s ppm, Temperature %s degC|", gasBuffer, stc_tempBuffer);  // Full UI printout
        sprintf(printBuffer, "%s: %5s, ", CD3.ID, stc_gasBuffer);  // just the data
        Serial.print(printBuffer);
      }
      if (CD4_ACTIVE) {
        char stc_gasBuffer[6];
        char stc_tempBuffer[6];
        dtostrf(CD4_data.gasConcentration, 4, 2, stc_gasBuffer);
        dtostrf(CD4_data.gasTemperature, 4, 2, stc_tempBuffer);
        //sprintf(printBuffer, "| STC31: CO2: %s ppm, Temperature %s degC|", gasBuffer, stc_tempBuffer);  // Full UI printout
        sprintf(printBuffer, "%s: %5s, ", CD4.ID, stc_gasBuffer);  // just the data
        Serial.print(printBuffer);
      }
      if (CD5_ACTIVE) {
        char stc_gasBuffer[6];
        char stc_tempBuffer[6];
        dtostrf(CD5_data.gasConcentration, 4, 2, stc_gasBuffer);
        dtostrf(CD5_data.gasTemperature, 4, 2, stc_tempBuffer);
        //sprintf(printBuffer, "| STC31: CO2: %s ppm, Temperature %s degC|", gasBuffer, stc_tempBuffer);  // Full UI printout
        sprintf(printBuffer, "%s: %5s, ", CD5.ID, stc_gasBuffer);  // just the data
        Serial.print(printBuffer);
      }
      if (CD6_ACTIVE) {
        char stc_gasBuffer[6];
        char stc_tempBuffer[6];
        dtostrf(CD6_data.gasConcentration, 4, 2, stc_gasBuffer);
        dtostrf(CD6_data.gasTemperature, 4, 2, stc_tempBuffer);
        //sprintf(printBuffer, "| STC31: CO2: %s ppm, Temperature %s degC|", gasBuffer, stc_tempBuffer);  // Full UI printout
        sprintf(printBuffer, "%s: %5s, ", CD6.ID, stc_gasBuffer);  // just the data
        Serial.print(printBuffer);
      }

      if (RHT3_ACTIVE) {
        char sht_tempBuffer[8];
        char sht_humidBuffer[8];
        dtostrf(RHT3_data.temperature, 4, 2, sht_tempBuffer);
        dtostrf(RHT3_data.humidity, 4, 2, sht_humidBuffer);
        //sprintf(printBuffer, "| SHT41: Temperature: %s degC, Humidity: %s %% |", sht_tempBuffer, sht_humidBuffer); // Full UI Printout
        sprintf(printBuffer, "%s: %5s, %5s, ", RHT3.ID, sht_tempBuffer, sht_humidBuffer);  // just the data
        Serial.print(printBuffer);
      }
      if (RHT4_ACTIVE) {
        char sht_tempBuffer[8];
        char sht_humidBuffer[8];
        dtostrf(RHT4_data.temperature, 4, 2, sht_tempBuffer);
        dtostrf(RHT4_data.humidity, 4, 2, sht_humidBuffer);
        //sprintf(printBuffer, "| SHT41: Temperature: %s degC, Humidity: %s %% |", sht_tempBuffer, sht_humidBuffer); // Full UI Printout
        sprintf(printBuffer, "%s: %5s, %5s, ", RHT4.ID, sht_tempBuffer, sht_humidBuffer);  // just the data
        Serial.print(printBuffer);
      }
      if (RHT5_ACTIVE) {
        char sht_tempBuffer[8];
        char sht_humidBuffer[8];
        dtostrf(RHT5_data.temperature, 4, 2, sht_tempBuffer);
        dtostrf(RHT5_data.humidity, 4, 2, sht_humidBuffer);
        //sprintf(printBuffer, "| SHT41: Temperature: %s degC, Humidity: %s %% |", sht_tempBuffer, sht_humidBuffer); // Full UI Printout
        sprintf(printBuffer, "%s: %5s, %5s, ", RHT5.ID, sht_tempBuffer, sht_humidBuffer);  // just the data
        Serial.print(printBuffer);
      }
      if (RHT6_ACTIVE) {
        char sht_tempBuffer[8];
        char sht_humidBuffer[8];
        dtostrf(RHT6_data.temperature, 4, 2, sht_tempBuffer);
        dtostrf(RHT6_data.humidity, 4, 2, sht_humidBuffer);
        //sprintf(printBuffer, "| SHT41: Temperature: %s degC, Humidity: %s %% |", sht_tempBuffer, sht_humidBuffer); // Full UI Printout
        sprintf(printBuffer, "%s: %5s, %5s, ", RHT6.ID, sht_tempBuffer, sht_humidBuffer);  // just the data
        Serial.print(printBuffer);
      }
      if (dP1_ACTIVE) {
        char sdp_diffPressureBuffer[8];
        char sdp_tempBuffer[8];
        dtostrf(dP1_data.diffPressure, 4, 2, sdp_diffPressureBuffer);
        dtostrf(dP1_data.temp, 4, 2, sdp_tempBuffer);
        sprintf(printBuffer, "%s: %5s, %5s, ", dP1.ID, sdp_diffPressureBuffer, sdp_tempBuffer);  // just the data
        Serial.print(printBuffer);
      }
      if (dP2_ACTIVE) {
        char sdp_diffPressureBuffer[8];
        char sdp_tempBuffer[8];
        dtostrf(dP2_data.diffPressure, 4, 2, sdp_diffPressureBuffer);
        dtostrf(dP2_data.temp, 4, 2, sdp_tempBuffer);
        sprintf(printBuffer, "%s: %5s, %5s, ", dP2.ID, sdp_diffPressureBuffer, sdp_tempBuffer);  // just the data
        Serial.print(printBuffer);
      }
      if (dP3_ACTIVE) {
        char sdp_diffPressureBuffer[8];
        char sdp_tempBuffer[8];
        dtostrf(dP3_data.diffPressure, 4, 2, sdp_diffPressureBuffer);
        dtostrf(dP3_data.temp, 4, 2, sdp_tempBuffer);
        sprintf(printBuffer, "%s: %5s, %5s, ", dP3.ID, sdp_diffPressureBuffer, sdp_tempBuffer);  // just the data
        Serial.print(printBuffer);
      }

      Serial.println();  // Send line return once all data has been sent
    }
    numSamples++;
  }
}
