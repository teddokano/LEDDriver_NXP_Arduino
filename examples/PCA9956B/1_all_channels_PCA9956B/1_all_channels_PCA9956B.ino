/** PCA9956B LED driver operation sample
 *  
 *  This sample code is showing PCA9956B LED driver operation with PWM value setting change.
 *  Check all channels with PWM dimming
 *
 *  @author  Tedd OKANO
 *
 *  Released under the MIT license License
 *
 *  About PCA9956B:
 *    https://www.nxp.com/products/power-management/lighting-driver-and-controller-ics/led-drivers/24-channel-fm-plus-ic-bus-57-ma-20-v-constant-current-led-driver:PCA9956BTW
 */

#include <LEDDriver.h>

PCA9956B ledd;

void setup() {
  Serial.begin(9600);
  Serial.println("\r***** Hello, PCA9956B! *****");

  Wire.begin();
  ledd.begin(1.0, PCA9956B::ARDUINO_SHIELD);
}

void loop() {
  for (int ch = 0; ch < ledd.n_channel; ch++) {
    for (int i = 0; i < 256; i++) {
      ledd.pwm(ch, i / 255.0);
      delay(1);
    }
    for (int i = 255; 0 <= i; i--) {
      ledd.pwm(ch, i / 255.0);
      delay(1);
    }
  }
}
