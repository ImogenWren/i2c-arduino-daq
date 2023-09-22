
#include <SensirionI2CScd4x.h>

SensirionI2CScd4x scd4x;

bool scd41_DataReady = false;  // Dont like as global but quick fix

struct scd41_Data {
  uint16_t CO2;
  float temperature;
  float humidity;
};

/*
void printUint16Hex(uint16_t value) {
  Serial.print(value < 4096 ? "0" : "");
  Serial.print(value < 256 ? "0" : "");
  Serial.print(value < 16 ? "0" : "");
  Serial.print(value, HEX);
}

void printSerialNumber(uint16_t serial0, uint16_t serial1, uint16_t serial2) {
  Serial.print("Serial: 0x");
  printUint16Hex(serial0);
  printUint16Hex(serial1);
  printUint16Hex(serial2);
  Serial.println();
}
*/

void scd41_Setup() {
  Serial.println("\nSCD41 - CO2 - Temp - Humidity Sensor - Starting");

  uint16_t error;
 // char errorMessage[128];

  scd4x.begin(Wire);

  // stop potentially previously started measurement
  error = scd4x.stopPeriodicMeasurement();
  if (error) {
    Serial.print("Error executing stopPeriodicMeasurement(): ");
    //errorToString(error, errorMessage, 256);
  //  Serial.println(errorMessage);
  }

  uint16_t serial0;
 uint16_t serial1;
  uint16_t serial2;
  error = scd4x.getSerialNumber(serial0, serial1, serial2);
  if (error) {
    Serial.print("Error executing getSerialNumber(): ");
  //  errorToString(error, errorMessage, 256);
  //  Serial.println(errorMessage);
  } else {
 //   printSerialNumber(serial0, serial1, serial2);
  }

  // Start Measurement
  error = scd4x.startPeriodicMeasurement();
  if (error) {
    Serial.print("Error executing startPeriodicMeasurement(): ");
  //  errorToString(error, errorMessage, 256);
   // Serial.println(errorMessage);
  }

  Serial.println("Waiting for first measurement... (5 sec)");
}

 // scd41_Data SCD41_data; // making this global so this function can just update the global variable every time new data is available.

scd41_Data scd41_Loop() {
  scd41_Data SCD41_data;

  uint16_t error;
 // char errorMessage[64];

  // Read Measurement
  uint16_t co2 = 0;
  float temperature = 0.0f;
  float humidity = 0.0f;
  scd41_DataReady = false;
  error = scd4x.getDataReadyFlag(scd41_DataReady);
  if (error) {
    Serial.print("Error executing getDataReadyFlag(): ");
   // errorToString(error, errorMessage, 128);
   // Serial.println(errorMessage);
    return;
  }
  if (!scd41_DataReady) {
    return;
  }
  error = scd4x.readMeasurement(co2, temperature, humidity);
  if (error) {
    Serial.print("Error executing readMeasurement(): ");
 //   errorToString(error, errorMessage, 256);
 //   Serial.println(errorMessage);
    return;
  } else if (co2 == 0) {
    Serial.println("Invalid sample detected, skipping.");
    return;
  } else {
    //Serial.print("CO2:");
    //Serial.print(co2);
    //Serial.print("\t");
    //Serial.print("Temperature:");
    //Serial.print(temperature);
    //Serial.print("\t");
    //Serial.print("Humidity:");
    //Serial.println(humidity);
    SCD41_data = { co2, temperature, humidity };
    return SCD41_data;
  }
}