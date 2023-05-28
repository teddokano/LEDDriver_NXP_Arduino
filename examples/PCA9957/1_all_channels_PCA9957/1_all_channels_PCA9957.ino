/** PCA9957 LED driver operation sample
 *  
 *  This sample code is showing PCA9957 LED driver operation with PWM value setting change.
 *  Check all channels with PWM dimming
 *
 *  @author  Tedd OKANO
 *
 *  Released under the MIT license License
 *
 *  About PCA9957:
 *    https://www.nxp.com/products/power-management/lighting-driver-and-controller-ics/led-drivers/24-channel-spi-serial-bus-32-ma-5-5-v-constant-current-led-driver:PCA9957
 */

#include <PCA9957.h>

PCA9957 ledd;

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;

  SPI.begin();
  ledd.begin(1.0, PCA9957::ARDUINO_SHIELD);

  Serial.println("\r***** Hello, PCA9957! *****");
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
