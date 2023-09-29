/* # European Project i2c Sensor Mux - MAIN


List of Sensors and Mux Channel Numbers
Mux 0 = i2c bus from nano
Mux 1 = Mux Module 1
Mux 2 = Mux Module 2 (for later expansion if required)
 
|No. |Sensor Name (system)  |	Sensor Type (model) |	Data Returned       |	Units                 |	Sample Rate  (Hz or every X seconds)| Mux.Channel  |
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


// define the active sensors
bool CD1_ACTIVE = false;
bool CD2_ACTIVE = false;
bool CD3_ACTIVE = true;
bool CD4_ACTIVE = false;
bool CD5_ACTIVE = false;
bool CD6_ACTIVE = false;
bool RHT3_ACTIVE = false;
bool RHT4_ACTIVE = false;
bool RHT5_ACTIVE = false;
bool RHT6_ACTIVE = false;




#include <Wire.h>
#include "i2c-utils.h"
#include "UI-utils.h"


#include <autoDelay.h>
autoDelay printDelay;
#define PRINT_DELAY_S 6



// Create instances for each sensor
#include "SCD41.h"
SCD41 CD1;  // Create instance of SCD41 for CD1
SCD41 CD2;  // Create instance of SCD41 for CD2

#include "STC31.h"
STC31 CD3;  // Create instance of STC31 for CD3



void setup() {
  Serial.begin(115200);
  Serial.println("\nSensor i2c Mux");
  delay(500);
  setupMux();
  delay(500);
  Serial.println("Begin Sensor Setup");

  sensorMux.setPort(0);  // Ensure that sensors with the same ID are not connected to the same port
  if (CD1_ACTIVE) { CD1.scd41_Setup(); }
  if (CD3_ACTIVE) { CD3.stc31_Setup(); }
  sensorMux.setPort(1);  //
  if (CD2_ACTIVE) { CD2.scd41_Setup(); }


  printDataHeader();  // Data header tells user order of data returned via serial
}



uint16_t numSamples = 0;

void loop() {



  SCD41::scd41_Data CD1_data;  // Return types for SCD data
  SCD41::scd41_Data CD2_data;  // Return types for SCD data

  STC31::stc31_Data CD3_data;  // Return types for STC Data

  sensorMux.setPort(0);  //  Change port address to 0 and read all sensors on 0

  if (CD1_ACTIVE) { CD1_data = CD1.scd41_Loop(); }  // This only updates data ~ every 5 seconds
  if (CD3_ACTIVE) { CD3_data = CD3.stc31_Loop(); }  //

  sensorMux.setPort(1);  //  Change port address to 1 and read all sensors on 1

  if (CD2_ACTIVE) { CD2_data = CD2.scd41_Loop(); }  // This only updates data ~ every 5 seconds


  if (printDelay.secondsDelay(PRINT_DELAY_S)) {
    char printBuffer[128];  // all sensors share single print buffer

    if (numSamples > 0) {  //skip printing the 0 sample for stability
      if (CD1_ACTIVE) {
        char scd_tempBuffer[6];
        char scd_humidBuffer[6];
        dtostrf(CD1_data.temperature, 4, 2, scd_tempBuffer);
        dtostrf(CD1_data.humidity, 4, 2, scd_humidBuffer);
        sprintf(printBuffer, "%03i:  %4i, %s, %s,", numSamples, CD1_data.CO2, scd_tempBuffer, scd_humidBuffer);  // Just the Data
        Serial.print(printBuffer);
      }
      if (CD2_ACTIVE) {
        char scd_tempBuffer[6];
        char scd_humidBuffer[6];
        dtostrf(CD2_data.temperature, 4, 2, scd_tempBuffer);
        dtostrf(CD2_data.humidity, 4, 2, scd_humidBuffer);
        sprintf(printBuffer, "%03i:  %4i, %s, %s,", numSamples, CD2_data.CO2, scd_tempBuffer, scd_humidBuffer);  // Just the Data
        Serial.print(printBuffer);
      }

      if (CD3_ACTIVE) {
        char stc_gasBuffer[6];
        char stc_tempBuffer[6];
        dtostrf(CD3_data.gasConcentration, 4, 2, stc_gasBuffer);
        dtostrf(CD3_data.gasTemperature, 4, 2, stc_tempBuffer);
        //sprintf(printBuffer, "| STC31: CO2: %s ppm, Temperature %s degC|", gasBuffer, stc_tempBuffer);  // Full UI printout
        sprintf(printBuffer, " %s,", stc_gasBuffer);  // just the data
        Serial.print(printBuffer);
      }


      Serial.println();
    } else {
      // Skip sample 0
    }
    numSamples++;
  } else {
  }
}
