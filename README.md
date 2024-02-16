# i2c Sensor Breakout Board for Data Aquisition Tasks
Flexible system for gathering i2c sensor data and providing sources to Data Aquisition software (LabVIEW, Python, Matlab, Terra Term, etc)

_The included firmware shows how to wrap up any external sensor library into a flexible format that allows easy modification to existing system and easy addition of 
new sensors._

_PCB Developed for use with Senserion i2c sensors, though is compatable with any i2c enabled periferal devices_

- Data output in CSV format over USB Serial connection as MVP for communications or logging with external software
- Could be improved by the addition of ModBus or JSON formatted data communication with error checking

## PCB

![image](https://github.com/ImogenWren/i2c-arduino-daq/assets/97303986/00418a14-c129-4d94-9d56-caf41dc0b3b5)


## Hardware Required
- Arduino Nano (PCB designed for this footprint, but other Arduino boards are compatable)
	- SDA A4
	- SCL A5
	
- DAQ (Data AQuisition) PCB
- Logging software
- USB port


## Sensirion SCD41 - CO2 Sensor - i2c
 - 5v or 3.3v


## Sensirion SEK-STC31 - CO2 Sensor - i2c

- 5v or 3.3v (calibrated for 3.3v)

 - Pinout: 
	- Vdd: brown    green
	- SCL: green    brown
	- GND: pink 	pink
	- SDA: yellow	Yellow
 
# Everything LabView

