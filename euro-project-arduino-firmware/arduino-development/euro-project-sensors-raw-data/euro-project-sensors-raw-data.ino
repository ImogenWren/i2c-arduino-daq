/* # European Project i2c Sensor Mux

_Sample all sensors and print to serial monitor in predefined order_


### List of Sensors and Mux Channel Numbers
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



### I2C Controller Pin Definition:
_See sensor header files for sensor node I2C pin definitions_


 ## Arduino Nano/Uno
| Pin | Function  | Wire Colour (Probably) |
|---  |---        |---                     |   
| A4  | SDA       |  Green                 |
| A5  | SLA       |  Yellow                |


### Data Output Order:
_Data is output in a single message with every data value and no checksum_
- Future improvements:
  - Use JSON format to pack and unpack data
```
CD1.CO2, CD1.temp, CD1.humidity,
CD2.CO2, CD2.temp, CD2.humidity,
CD3.CO2,
CD4.CO2,
CD5.CO2,
CD6.CO2,
RHT3.temp, RHT3.humidity, 
RHT4.temp, RHT4.humidity, 
RHT5.temp, RHT5.humidity, 
RHT6.temp, RHT6.humidity
```
 */

#include <Arduino.h>
#include <Wire.h>


#include <autoDelay.h>
autoDelay printDelay;
#define PRINT_DELAY_S 6

// If Init as true, program will test sensor and if missing, will report then block action of sensor
bool SCD41_ACTIVE = true;
bool STC31_ACTIVE = true;
bool SHT41_ACTIVE = true;

#include "SCD41-CO2-sensor.h"
#include "STC31-CO2-sensor.h"
#include "SHT41-HT-sensor.h"
//#include "ACS70331-current-sensor.h" Not required for Arduino


void printDataHeader(){
  Serial.println("SDC41:CO2,Temp,Humid,STC31:CO2,SHT:Temp,Humid,");
}


void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(100);
  }
  Serial.println("\n\nEuropean Project - i2c Sensor Interface");
  delay(1000);
  Wire.begin();
  if (SCD41_ACTIVE){
  scd41_Setup();
  }
  if (STC31_ACTIVE){
  stc31_Setup(); 
  }
  if (SHT41_ACTIVE){
   sht41_Setup();
  }
  // ACS70331_Setup();
  printDataHeader();
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
  STC31_data = stc31_Loop();

  sht41_Data SHT41_data;
  char sht_humidBuffer[8];
  char sht_tempBuffer[8];
  SHT41_data = sht41_Loop();




/*
  if (scd41_DataReady ) {  // print data if sensor has new data - DISABLED for now
    sampleData = true;
  }
*/


  if (printDelay.secondsDelay(PRINT_DELAY_S)) {
  
  //  if (sampleData) {

      if (SCD41_ACTIVE){
      dtostrf(SCD41_data.temperature, 4, 2, scd_tempBuffer);
      dtostrf(SCD41_data.humidity, 4, 2, humidBuffer);
      //sprintf(printBuffer, "| SCD41: CO2: %4i ppm, Temperature: %s degC, Humidity: %s %% |", SCD41_data.CO2, scd_tempBuffer, humidBuffer);
      sprintf(printBuffer, "%4i, %s, %s,", SCD41_data.CO2, scd_tempBuffer, humidBuffer);
      Serial.print(printBuffer);
      }

      if (STC31_ACTIVE){
      dtostrf(STC31_data.gasConcentration, 4, 2, gasBuffer);
      dtostrf(STC31_data.gasTemperature, 4, 2, stc_tempBuffer);
      //sprintf(printBuffer, "| STC31: CO2: %s ppm, Temperature %s degC|", gasBuffer, stc_tempBuffer);
      sprintf(printBuffer, " %s,", gasBuffer);
      Serial.print(printBuffer);
      }

      if (SHT41_ACTIVE){
      dtostrf(SHT41_data.temperature, 4, 2, sht_tempBuffer);
      dtostrf(SHT41_data.humidity, 4, 2, sht_humidBuffer);
      //sprintf(printBuffer, "| SHT41: Temperature: %s degC, Humidity: %s %% |", sht_tempBuffer, sht_humidBuffer);
      sprintf(printBuffer, " %s, %s", sht_tempBuffer, sht_humidBuffer);
      Serial.print(printBuffer);
      }

      //  countdown = 6;
      Serial.println();
      sampleData = false;
  //  }
  } else {
    // Just for debugging timings
    // Serial.print("Count: ");
    // Serial.println(countdown);
    //countdown--;
  }
}
