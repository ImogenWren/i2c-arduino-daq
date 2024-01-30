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


#include <Arduino.h>
#include <Wire.h>

#pragma once

#ifndef SDP810_h
#define SDP810_h

#include <SensirionI2CSdp.h>

class SDP810 {

public:
  SensirionI2CSdp sdp;

  struct sdp810_Data {
    float diffPressure;
    float temp;
  };

    // Constructor
  SDP810() {
  }

  void sdp810_Setup();

  sdp810_Data sdp810_Loop();

private:
};



#endif