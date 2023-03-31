/** PCT2075 temperature sensor operation sample
 *  
 *  This sample code is showing PCT2075 temperature sensor operation with interrupt.
 *  "Tos" and "Thyst" are set to generate interrupt.   
 *
 *  @author  Tedd OKANO
 *
 *  Released under the MIT license License
 *
 *  About PCT2075:
 *    https://www.nxp.jp/products/sensors/ic-digital-temperature-sensors/ic-bus-fm-plus-1-degree-c-accuracy-digital-temperature-sensor-and-thermal-watchdog:PCT2075
 */


#include "LEDDriver.h"

PCA9956B ledd;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("\r***** Hello, PCA9955B! *****");

  I2C_device::scan();
  ledd.begin(0.1, PCA9955B::ARDUINO_SHIELD);
}

void loop() {
  for (int ch = 0; ch < ledd.n_channel; ch++){
    for ( int i = 0; i < 256; i++ ) {
      ledd.pwm(ch, i / 255.0);
      delay(1);
    }
    for ( int i = 255; 0 <= i; i-- ) {
      ledd.pwm(ch, i / 255.0);
      delay(1);
    }
  }
}
