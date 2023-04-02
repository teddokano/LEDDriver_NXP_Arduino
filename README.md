# LEDDriver_NXP_Arduino
LED driver device operation sample code for [Arduino](https://www.arduino.cc) 

> **Note**
This library works with [`I2C_device`](https://github.com/teddokano/I2C_device_Arduino) library together. Please be sure the `I2C_device` library is imported in your environment before trying to build. 

![Boards](https://github.com/teddokano/additional_files/blob/main/LEDDriver_NXP_Arduino/LED-ARD.jpeg)  
**THIS PICTURE WILL BE REPLACED**
_PCA9955BTW-ARD : Arduino® Shield Evaluation Board for PCA9955B LED driver_

# What is this?
An Arduino library for I²C LED drivers with sample code.  
The I²C temperature sensors can measure temoperature and output comparator or interrupt signals by threshold settings. 

# Supported devices
Type#|Features|# of channels|additional feature|Interface|Evaluation board
---|---|---|---|---|---
[PCA9955B](https://www.nxp.com/products/power-management/lighting-driver-and-controller-ics/led-drivers/16-channel-fm-plus-ic-bus-57-ma-20-v-constant-current-led-driver:PCA9955BTW)	|Constant current LED driver	|16ch		|with gradation control	|I²C Fast-mode plus (1MHz)			|[PCA9955BTW-ARD LED Driver Arduino® Shield Evaluation Board](https://www.nxp.com/design/development-boards/analog-toolbox/arduino-shields-solutions/pca9955btw-ard-led-driver-arduino-shield-evaluation-board:PCA9955BTW-ARD?tid=vanPCA9955BTW-ARD)
[PCA9956B](https://www.nxp.jp/products/power-management/lighting-driver-and-controller-ics/led-drivers/24-channel-fm-plus-ic-bus-57-ma-20-v-constant-current-led-driver:PCA9956BTW)		|Constant current LED driver	|24ch		|---					|I²C Fast-mode plus (1MHz)			|[OM13321](https://www.nxp.com/docs/en/user-guide/UM10709.pdf)
[PCA9957](https://www.nxp.jp/products/power-management/lighting-driver-and-controller-ics/led-drivers/24-channel-spi-serial-bus-32-ma-5-5-v-constant-current-led-driver:PCA9957)		|Constant current LED driver	|24ch		|with gradation control	|SPI								|[PCA9957HN-ARD LED Driver Arduino® Shield Evaluation Board](https://www.nxp.jp/design/development-boards/analog-toolbox/arduino-shields-solutions/pca9957hn-ard-led-driver-arduino-shield-evaluation-board:PCA9957HN-ARD)

To put PCA9957HN-ARD Arduino-shield evaluation board, use socket-pin extenders to avoid down side connector interfare.  
![Boards](https://github.com/teddokano/additional_files/blob/main/LEDDriver_NXP_Arduino/PCA9957_pins.jpeg)

# Code sample
With `LEDDriver_NXP_Arduino` library, the LEDs can be managed simple API.  
For PCA9955B and PCA9956B, those operations are quite similar. When the device is changed, just overwrite class name from `PCA9955B` to `PCA9956B`.  

```cpp
#include <LEDDriver.h>

PCA9955B ledd;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("\r***** Hello, PCA9955B! *****");
  I2C_device::scan();
  ledd.begin(1.0, PCA9955B::ARDUINO_SHIELD);
}

void loop() {
  ledd.pwm(0, 0xFF);
  Serial.println("ON");
  delay(100);

  ledd.pwm(0, 0x00);
  Serial.println("OFF");
  delay(100);
}
```

For PCA9957, it uses an SPI as serial interface. To use the SPI, need to have `SPI.begin()` in `setup()` function. 
```cpp
#include "LEDDriver.h"

PCA9957 ledd;

void setup() {
  SPI.begin();	//	<-- **** to use SPI ****
  Serial.begin(9600);
  Serial.println("\n***** Hello, PCA9957! *****");
  ledd.begin(1.0, PCA9957::ARDUINO_SHIELD);
}

void loop() {
  ledd.pwm(0, 0xFF);
  Serial.println("ON ");
  delay(100);

  ledd.pwm(0, 0x00);
  Serial.println("OFF");
  delay(100);
}
```  



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
`PCA9955B`, `PCA9956B` and `PCA9957` class libraries are included. Those libraries can be used by just making an instance from those class.  
Those libraries have common methods to get/set device information.

Method|Role
---|---
`begin( float current = 0.1, board env = NONE )`	|Initializing device. 1st argument `current` is ratio of output current. 0.0~1.0. 2nd argument `env` is an option: use `LEDDriver::ARDUINO_SHIELD` if the target board is Arduino-shield board
`pwm( uint8_t ch, float value )`					|Set single channel LED brightness. `value` must be in float: 0.0~1.0
`void pwm( float* values )`							|Set LED brightness for all channels. `values` must be an array of float with length of number of device output channels. Each float values in the array should be 0.0~1.0.
					|Set high and low temperature threshold for OS output. `v0` and `v1` are needed to be given by Celsius value. Order of the arguments doesn't care

## Examples
Example code is provided as scketch files.  
For a quick access to those sketch, **refer to last step** of **"Getting started" section** of [TempSensor_NXP_Arduino](https://github.com/teddokano/TempSensor_NXP_Arduino/blob/main/README.md) page (README.md). 

Sketch|Feature
---|---
PCA9955B_simple_ch0							|Simple sample for just blinking channel 0
PCA9956B_simple_ch0							|Simple sample for just blinking channel 0
PCA9957_simple_ch0							|Simple sample for just blinking channel 0

# Document
For details of the library, please find descriptions in [this document](https://teddokano.github.io/LEDDriver_NXP_Arduino/annotated.html).

# References
