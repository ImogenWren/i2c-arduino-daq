/*
 * I2C-Generator: 0.2.0
 * Yaml Version: 0.1.0
 * Template Version: 0.7.0-38-g217adaf
 */
/*
 * Copyright (c) 2021, Sensirion AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Sensirion AG nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */


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

SDP810 dP1;  // Create instance of SDP810 for dP1
SDP810 dP2;  // Create instance of SDP810 for dP2
SDP810 dP3;  // Create instance of SDP810 for dP3

void setup() {
  Serial.begin(115200);
  Wire.begin();
  dP1.sdp810_Setup();
  delay(1000);
}




void loop() {
  // Set up variables to gather all sensor data
  SDP810::sdp810_Data dP1_data;  // return types for SDP810 data


  dP1_data = dP1.sdp810_Loop();

  char printBuffer[128];  // all sensors share single print buffer


  char sdp_diffPressureBuffer[8];
  char sdp_tempBuffer[8];
  dtostrf(dP1_data.diffPressure, 4, 2, sdp_diffPressureBuffer);
  dtostrf(dP1_data.temp, 4, 2, sdp_tempBuffer);

  sprintf(printBuffer, "%5s, %5s, ", sdp_diffPressureBuffer, sdp_tempBuffer);  // just the data

  delay(1000);
}
