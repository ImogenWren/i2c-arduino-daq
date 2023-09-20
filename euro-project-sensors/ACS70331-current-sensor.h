#define CURRENT_SENSE_PIN A1
#define SAMPLE_DELAY_mS 100
#define VOLTAGE_OFFSET 1.567

void ACS70331_Setup() {
  // Serial.begin(115200);
  Serial.println("\nACS70331 Current Sensor Starting");
}

float ADC_to_voltage(int16_t ADC_value) {
  float voltage = float(ADC_value) * (5.0 / 1024.0);
  return voltage;
}


float v_to_I(float voltage) {
  float current_mA = (voltage - VOLTAGE_OFFSET) * (1250);  // Not correct I dont think check tomorrow
  return current_mA;
}


// #TODO This need to return a float
float ACS70331_Loop() {

  int16_t ADC_value = analogRead(CURRENT_SENSE_PIN);
  float voltage = ADC_to_voltage(ADC_value);
  //  float current = ADC_to_current(ADC_value);
  float current = v_to_I(voltage);
  // Serial.println(current);
  char voltStr[12];
  char currentStr[12];
  dtostrf(voltage, 4, 3, voltStr);
  dtostrf(current, 4, 2, currentStr);
  char printBuffer[64];
  sprintf(printBuffer, "ADC_value: %4i, V_measured: %4s V, I: %s mA", ADC_value, voltStr, currentStr);
  Serial.println(printBuffer);

  return current;
}