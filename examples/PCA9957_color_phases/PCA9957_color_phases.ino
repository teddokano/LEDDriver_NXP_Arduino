/** PCA9957 LED driver operation sample
 *  
 *  This sample code is showing PCA9957 LED driver operation with PWM value setting change.
 *  The ledd.pwm() takes an array of 24 float values to change LED brightness at once
 *
 *  @author  Tedd OKANO
 *
 *  Released under the MIT license License
 *
 *  About PCA9957:
 *    https://www.nxp.jp/products/power-management/lighting-driver-and-controller-ics/led-drivers/24-channel-spi-serial-bus-32-ma-5-5-v-constant-current-led-driver:PCA9957
 */

#include <LEDDriver.h>

#define COLOR_LED_ONLY

PCA9957 ledd;

void setup() {
  Serial.begin(9600);
  Serial.println("\r***** Hello, PCA9957! *****");

  SPI.begin();
  ledd.begin(1.0, PCA9957::ARDUINO_SHIELD);
}

void loop() {
  float v[ledd.n_channel] = { 0.0 };
  int cycle = 60;
  float pwm;
  int ch;

#ifdef COLOR_LED_ONLY
  int n_ch = 12;
#else
  int n_ch = ledd.n_channel;
#endif

  for (int i = 0; i < cycle; i++) {
    for (int offset = 0; offset < n_ch; offset++) {
      pwm = sin(PI * ((i + cycle * (offset / (float)n_ch)) / (float)cycle));
      pwm = pow(pwm, 4);
      ch = (offset * 4) % n_ch + (offset * 4) / n_ch;
      v[ch] = pwm;
    }
    ledd.pwm(v);
    delay(20);
  }
}
