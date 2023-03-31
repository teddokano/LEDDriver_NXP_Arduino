# LEDDriver_NXP_Arduino
LED driver device operation sample code for [Arduino](https://www.arduino.cc) 

> **Note**
This library works with [`I2C_device`](https://github.com/teddokano/I2C_device_Arduino) library together. Please be sure the `I2C_device` library is imported in your environment before trying to build. 

![Boards](https://github.com/teddokano/additional_files/blob/main/TempSensor_NXP_Arduino/TempSensors.jpg)  
**THIS PICTURE WILL BE REPLACED**
_PCA9955BTW-ARD : Arduino® Shield Evaluation Board for PCA9955B LED driver_

# What is this?
An Arduino library for I²C LED drivers with sample code.  
The I²C temperature sensors can measure temoperature and output comparator or interrupt signals by threshold settings. 

With `LEDDriver_NXP_Arduino` library, the LEDs can be managed simple API. 
```cpp
#include "LEDDriver.h"

PCA9955B ledd;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("\r***** Hello, PCA9955B! *****");
  ledd.begin( 0.1, PCA9955B::ARDUINO_SHIELD );
}

void loop() {
  ledd.pwm( 0, 0xFF );
  Serial.println("\rON");
  delay(100);

  ledd.pwm( 0, 0x00 );
  Serial.println("\rOFF");
  delay(100);
}
```

# Supported devices
Type#|Features|# of channels|additional feature|Interface|Evaluation board
---|---|---|---|---|---
[PCA9955B](https://www.nxp.com/products/power-management/lighting-driver-and-controller-ics/led-drivers/16-channel-fm-plus-ic-bus-57-ma-20-v-constant-current-led-driver:PCA9955BTW)	|Constant current LED driver	|16ch		|with gradation control	|I²C Fast-mode plus (1MHz)			|[PCA9955BTW-ARD LED Driver Arduino® Shield Evaluation Board](https://www.nxp.com/design/development-boards/analog-toolbox/arduino-shields-solutions/pca9955btw-ard-led-driver-arduino-shield-evaluation-board:PCA9955BTW-ARD?tid=vanPCA9955BTW-ARD)
[PCA9956B](https://www.nxp.jp/products/power-management/lighting-driver-and-controller-ics/led-drivers/24-channel-fm-plus-ic-bus-57-ma-20-v-constant-current-led-driver:PCA9956BTW)		|Constant current LED driver	|24ch		|---					|I²C Fast-mode plus (1MHz)			|[OM13321](https://www.nxp.com/docs/en/user-guide/UM10709.pdf)

# Getting started
For importing library and run the sample code, please find **Getting started** page (README.md) of [TempSensor_NXP_Arduino](https://github.com/teddokano/TempSensor_NXP_Arduino/blob/main/README.md). 
<!--
Use **Library manager** in Arduino IDE for easy install
- **Find** this library: **Open** the _**Library Manager**_ pane, **Search** this library and click **INSTALL** button.  
![Find the lib](https://github.com/teddokano/additional_files/blob/main/TempSensor_NXP_Arduino/LM_install0s.png)

- Click **"INSTALL ALL"**  
![Install all](https://github.com/teddokano/additional_files/blob/main/TempSensor_NXP_Arduino/LM_install1s.png)

- Install will be completed quickly  
![Install completed](https://github.com/teddokano/additional_files/blob/main/TempSensor_NXP_Arduino/LM_install2s.png)

- Choose a sample code and try!  
![Choosing a sample code](https://github.com/teddokano/additional_files/blob/main/TempSensor_NXP_Arduino/LM_install3s.png)
-->
# What's inside?
## **THIS SECTION WILL BE UPDATED** Temperature sensor library
`LM75B`, `PCT2075` and `P3T1085` class libraries are included. Those libraries can be used by just making an instance from those class.  
Those libraries have common methods to get/set device information.

Method|Role
---|---
temp()					|Get temperature in Celsius
thresholds( v0, v1 )	|Set high and low temperature threshold for OS output. `v0` and `v1` are needed to be given by Celsius value. Order of the arguments doesn't care
os_mode( mode )			|Set OS pin mode. It can be set comparator or interrupt mode. The argument needs to be given as a class constant like `PCT2075::COMPARATOR` or `PCT2075::INTERRUPT`. The class name can be `LM75B`, `PCT2075`, `P3T1085` or a generic name of `TempSensor`.

## Examples
Example code is provided as scketch files.  
For a quick access to those sketch, **refer to last step** of **"Getting started" section** of [TempSensor_NXP_Arduino](https://github.com/teddokano/TempSensor_NXP_Arduino/blob/main/README.md) page (README.md). 

Sketch|Feature
---|---
PCA9955B_simple							|Simple sample for just blinking channel 0
PCA9956B_simple							|Simple sample for just blinking all channels

# Document
For details of the library, please find descriptions in [this document](https://teddokano.github.io/LEDDriver_NXP_Arduino/annotated.html).

# References
