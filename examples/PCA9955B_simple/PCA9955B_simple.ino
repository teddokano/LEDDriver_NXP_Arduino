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

PCA9955B ledd;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("\r***** Hello, PCA9955B! *****");
  I2C_device::scan();
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