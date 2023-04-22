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
 *    https://www.nxp.com/products/power-management/lighting-driver-and-controller-ics/led-drivers/24-channel-fm-plus-ic-bus-57-ma-20-v-constant-current-led-driver:PCA9956BTW
 */

#include <PCA9956B.h>

PCA9956B ledd;

void setup() {
  Serial.begin(9600);
  Serial.println("\r***** Hello, PCA9955B! *****");

  Wire.begin();
  ledd.begin(1.0, PCA9956B::ARDUINO_SHIELD);
}

void loop() {
  float v[ledd.n_channel] = { 0.0 };
  int cycle = 200;
  float pwm;
  int n_ch = ledd.n_channel;

  for (int i = 0; i < cycle; i++) {
    for (int ch = 0, ofst = 0; ch < n_ch; ch++, ofst = (ch * (n_ch / 3) + (ch / 3)) % n_ch) {
      pwm = sin(2.0 * PI * ((i + cycle * (ofst / (float)n_ch)) / (float)cycle));
      pwm = pow(pwm, 4);
      //      pwm = (0.5 < pwm) ? 1.0 : 0.0;
      v[ch] = pwm;
    }
    ledd.pwm(v);
    delay(20);
  }
}
