
SensirionI2CStc3x stc3x;


struct stc31_Data {
  float gasConcentration;
  float gasTemperature;
};




void stc31_Setup() {
  Serial.println("\nSTC31 - CO2 - Temperature - Sensor - Starting");

  uint16_t error;
  // char errorMessage[64];

  stc3x.begin(Wire);

  error = stc3x.prepareProductIdentifier();
  if (error) {
    Serial.print("Error executing prepareProductIdentifier(): ");
    //  errorToString(error, errorMessage, 256);
    //  Serial.println(errorMessage);
  } else {
    uint32_t productNumber;
    uint8_t serialNumberRaw[32];
    uint8_t serialNumberSize = 32;
    error = stc3x.readProductIdentifier(productNumber, serialNumberRaw,
                                        serialNumberSize);
    if (error) {
      Serial.print("Error executing readProductIdentifier(): ");
      //   errorToString(error, errorMessage, 256);
      //   Serial.println(errorMessage);
    } else {
      //  uint64_t serialNumber = (uint64_t)serialNumberRaw[0] << 56 | (uint64_t)serialNumberRaw[1] << 48 | (uint64_t)serialNumberRaw[2] << 40 | (uint64_t)serialNumberRaw[3] << 32 | (uint64_t)serialNumberRaw[4] << 24 | (uint64_t)serialNumberRaw[5] << 16 | (uint64_t)serialNumberRaw[6] << 8 | (uint64_t)serialNumberRaw[7];
      Serial.print("ProductNumber: 0x");
      Serial.println(productNumber, HEX);
      //  char buffer[20];
      //  sprintf(buffer, "SerialNumber: %llu", serialNumber);
      //  Serial.println(buffer);
    }
    stc3x.enableAutomaticSelfCalibration();
   // stc3x.setBinaryGas(STC3X_BINARY_GAS_CO2_AIR_25);
  }





  uint16_t selfTestOutput;
  error = stc3x.selfTest(selfTestOutput);
  if (error) {
    Serial.print("Error trying to execute selfTest(): ");
    //   errorToString(error, errorMessage, 256);
    //   Serial.println(errorMessage);
  } else {
    char buffer[32];
    sprintf(buffer, "Self Test: 0x%04x (OK = 0x0000)", selfTestOutput);
    Serial.println(buffer);
  }

  error = stc3x.setBinaryGas(0x0001);
  if (error) {
    Serial.print("Error trying to execute selfTest(): ");
    //   errorToString(error, errorMessage, 256);
    //   Serial.println(errorMessage);
  } else {
    Serial.println("Set binary gas to 0x0001");
  }
}


stc31_Data stc31_Loop() {
  stc31_Data STC31_data;
  // Measure
  uint16_t gasTicks;
  uint16_t temperatureTicks;
  float temperature;
  float gasConcentration;
  uint16_t error;
  // char errorMessage[256];

  error = stc3x.measureGasConcentration(gasTicks, temperatureTicks);
  if (error) {
    Serial.print("Error executing measureGasConcentration(): ");
    //  errorToString(error, errorMessage, 256);
    //   Serial.println(errorMessage);
    return;
  } else {
  gasConcentration = 100 * ((float)gasTicks - 16384.0) / 32768.0;
 //. gasConcentration = (float)gasTicks - 15000;
    //  Serial.print("GasConcentration:");
    //   Serial.print(gasConcentration);
    //Serial.print();
    //   Serial.print("\t");
    //   Serial.print("Temperature:");
    temperature = (float)temperatureTicks / 200.0;
    //   Serial.println(temperature);
    STC31_data = { gasConcentration, temperature };
  }
  return STC31_data;
}