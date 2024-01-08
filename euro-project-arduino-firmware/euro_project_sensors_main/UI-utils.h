/*  UI Utilities


*/


void printDataHeader() {
  Serial.print("NumSamples,");
   if (CD1_ACTIVE) { Serial.print("CD1:(CO2,Temp,Humid),"); }
   if (CD2_ACTIVE) { Serial.print("CD2:(CO2,Temp,Humid),"); }
   if (CD3_ACTIVE) { Serial.print("CD3:(CO2),"); }
   if (CD4_ACTIVE) { Serial.print("CD4:(CO2),"); }
   if (CD5_ACTIVE) { Serial.print("CD5:(CO2),"); }
   if (CD6_ACTIVE) { Serial.print("CD6:(CO2),"); }
  if (RHT3_ACTIVE) { Serial.print("RHT3:(Temp,Humid),"); }
  if (RHT4_ACTIVE) { Serial.print("RHT4:(Temp,Humid),"); }
  if (RHT5_ACTIVE) { Serial.print("RHT5:(Temp,Humid),"); }
  if (RHT6_ACTIVE) { Serial.print("RHT6:(Temp,Humid),"); }
   Serial.println();  
}