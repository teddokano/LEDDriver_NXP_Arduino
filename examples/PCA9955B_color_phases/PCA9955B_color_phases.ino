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
 *    https://www.nxp.jp/products/power-management/lighting-driver-and-controller-ics/led-drivers/24-channel-spi-serial-bus-32-ma-5-5-v-constant-current-led-driver:PCA9955B
 */

#include <LEDDriver.h>

#define COLOR_LED_ONLY

PCA9955B ledd;

void setup() {
  Serial.begin(9600);
  Serial.println("\r***** Hello, PCA9955B! *****");

  Wire.begin();
  ledd.begin(0.01, PCA9955B::ARDUINO_SHIELD);
}

void loop() {
  float v[ledd.n_channel] = { 0.0 };
  int cycle = 60;
  float pwm;

#ifdef COLOR_LED_ONLY
  int n_ch = 9;
  //  const int order[] = { 0, 3, 6, 1, 4, 7, 2, 5, 8 };
  const int order[] = { 0, 4, 8, 1, 5, 6, 2, 3, 7 };
#else
  int n_ch = ledd.n_channel;
#endif
  for (int i = 0; i < cycle; i++) {
    for (int ch = 0, ofst = 0; ch < n_ch; ch++, ofst = (ofst + 5) % n_ch) {
      pwm = sin(PI * ((i + cycle * (ofst / (float)n_ch)) / (float)cycle));
      pwm = pow(pwm, 4);

      v[ch] = pwm;
    }
    ledd.pwm(v);
    delay(20);
  }
}
void loop2() {
  float v[ledd.n_channel] = { 0.0 };
  int cycle = 60;
  float pwm;
  int ch;

#ifdef COLOR_LED_ONLY
  int n_ch = 9;
  //  const int order[] = { 0, 3, 6, 1, 4, 7, 2, 5, 8 };
  const int order[] = { 0, 4, 8, 1, 5, 6, 2, 3, 7 };
#else
  int n_ch = ledd.n_channel;
#endif

  for (int i = 0; i < cycle; i++) {
    for (int ch = 0; ch < n_ch; ch++) {
      pwm = sin(PI * ((i + cycle * (((ch * 3 + ((ch * 3) / n_ch)) % n_ch) / (float)n_ch)) / (float)cycle));
      pwm = pow(pwm, 4);
      v[ch] = pwm;
    }
    ledd.pwm(v);
    delay(20);
  }
}
