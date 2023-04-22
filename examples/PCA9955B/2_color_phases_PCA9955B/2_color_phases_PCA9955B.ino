/** PCA9955B LED driver operation sample
 *  
 *  This sample code is showing PCA9955B LED driver operation with PWM value setting change.
 *  The ledd.pwm() takes an array of 24 float values to change LED brightness at once
 *
 *  @author  Tedd OKANO
 *
 *  Released under the MIT license License
 *
 *  About PCA9955B:
 *    https://www.nxp.com/products/power-management/lighting-driver-and-controller-ics/led-drivers/16-channel-fm-plus-ic-bus-57-ma-20-v-constant-current-led-driver:PCA9955BTW
 */

#include <PCA9955B.h>

#define COLOR_LED_ONLY

PCA9955B ledd;

void setup() {
  Serial.begin(9600);
  Serial.println("\r***** Hello, PCA9955B! *****");

  Wire.begin();
  ledd.begin(1.0, PCA9955B::ARDUINO_SHIELD);
}

void loop() {
  float v[ledd.n_channel] = { 0.0 };
  int cycle = 200;
  float pwm;

#ifdef COLOR_LED_ONLY
  int n_ch = 9;
#else
  int n_ch = ledd.n_channel;
#endif
  for (int i = 0; i < cycle; i++) {
    for (int ch = 0, ofst = 0; ch < n_ch; ch++, ofst = (ch * (n_ch / 3) + (ch /3)) % n_ch) {
      pwm = sin(2.0 * PI * ((i + cycle * (ofst / (float)n_ch)) / (float)cycle));
      pwm = pow(pwm, 4);
//      pwm = (0.5 < pwm) ? 1.0 : 0.0;
      v[ch] = pwm;
    }
    ledd.pwm(v);
    delay(20);
  }
}
