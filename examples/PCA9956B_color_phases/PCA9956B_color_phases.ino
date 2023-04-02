/** PCA9956B LED driver operation sample
 *  
 *  This sample code is showing PCA9956B LED driver operation with PWM value setting change.
 *  The ledd.pwm() takes an array of 24 float values to change LED brightness at once
 *
 *  @author  Tedd OKANO
 *
 *  Released under the MIT license License
 *
 *  About PCA9956B:
 *    https://www.nxp.jp/products/power-management/lighting-driver-and-controller-ics/led-drivers/24-channel-spi-serial-bus-32-ma-5-5-v-constant-current-led-driver:PCA9956B
 */

#include <LEDDriver.h>

PCA9956B ledd;

void setup() {
  Serial.begin(9600);
  Serial.println("\r***** Hello, PCA9955B! *****");

  Wire.begin();
  ledd.begin(0.1, PCA9956B::ARDUINO_SHIELD);
}

void loop() {
  float v[ledd.n_channel] = { 0.0 };
  int n_ch = ledd.n_channel;
  int cycle = 60;
  float pwm;

  for (int i = 0; i < cycle; i++) {
    for (int ch = 0, ofst = 0; ch < n_ch; ch++, ofst = (ofst + 5) % n_ch ) {
      pwm = sin(PI * ((i + cycle * (ofst / (float)n_ch)) / (float)cycle));
      pwm = pow(pwm, 4);

      v[ch] = pwm;
    }
    ledd.pwm(v);
    delay(20);
  }
}
