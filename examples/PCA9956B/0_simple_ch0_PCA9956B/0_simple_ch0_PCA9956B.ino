/** PCA9956B LED driver operation sample
 *  
 *  This sample code is showing PCA9956B LED driver operation with PWM value setting change.
 *  The ledd.pwm() takes channel number and PWM ratio. 
 *
 *  @author  Tedd OKANO
 *
 *  Released under the MIT license License
 *
 *  About PCA9956B:
 *    https://www.nxp.com/products/power-management/lighting-driver-and-controller-ics/led-drivers/24-channel-fm-plus-ic-bus-57-ma-20-v-constant-current-led-driver:PCA9956BTW
 */

#include <PCA9956B.h>

PCA9956B ledd;

void setup() {
  Serial.begin(9600);
  Serial.println("\n***** Hello, PCA9956B! *****");

  Wire.begin();
  ledd.begin(1.0, PCA9956B::ARDUINO_SHIELD);
}

void loop() {
  ledd.pwm(0, 1.0);
  Serial.println("ON ");
  delay(100);

  ledd.pwm(0, 0.0);
  Serial.println("OFF");
  delay(100);
}
