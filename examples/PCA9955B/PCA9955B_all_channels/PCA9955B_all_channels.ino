/** PCA9955B LED driver operation sample
 *  
 *  This sample code is showing PCA9955B LED driver operation with PWM value setting change.
 *  Check all channels with PWM dimming
 *
 *  @author  Tedd OKANO
 *
 *  Released under the MIT license License
 *
 *  About PCA9955B:
 *    https://www.nxp.jp/products/power-management/lighting-driver-and-controller-ics/led-drivers/24-channel-spi-serial-bus-32-ma-5-5-v-constant-current-led-driver:PCA9955B
 */

#include <LEDDriver.h>

PCA9955B ledd;

void setup() {
  Serial.begin(9600);
  Serial.println("\r***** Hello, PCA9955B! *****");

  Wire.begin();
  ledd.begin(1.0, PCA9955B::ARDUINO_SHIELD);
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
