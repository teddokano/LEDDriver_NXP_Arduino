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

PCA9957 ledd;

void setup() {
  SPI.begin();
  Serial.begin(9600);
  Serial.println("\n***** Hello, PCA9957 *****");
  ledd.begin(0.1, PCA9957::ARDUINO_SHIELD);
}

void loop() {
  ledd.pwm(0, 0xFF);
  Serial.println("ON ");
  delay(100);

  ledd.pwm(0, 0x00);
  Serial.println("OFF");
  delay(100);
}
