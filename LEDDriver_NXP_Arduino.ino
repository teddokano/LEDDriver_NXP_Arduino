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

PCA9956B ledd;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("\r***** Hello, PCA9955B! *****");

  I2C_device::scan();
  ledd.begin(0.1, PCA9955B::ARDUINO_SHIELD);
}

void loop() {
  int cycle = 60;
  float pwm;

#if 1
  int n_ch = ledd.n_channel;
  int ch;
  float v[n_ch];
  for (int i = 0; i < cycle; i++) {
    for (int offset = 0; offset < n_ch; offset++) {
      pwm = pow(sin(PI * ((i + cycle * (offset / (float)n_ch)) / (float)cycle)), 4);
      ch = (offset * 4) % n_ch + (offset * 4) / n_ch;
      v[ch] = pwm;
    }
    ledd.pwm(v);
    delay(20);
  }
#else
  int n_color = 3;

  for (int i = 0; i < cycle; i++) {
    for (int color = 0; color < n_color; color++) {
      pwm = pow(sin(PI * ((i + cycle * (color / (float)n_color)) / (float)cycle)), 4);

      for (int ch = 0; ch < ledd.n_channel; ch += n_color) {
        ledd.pwm(ch + color, pwm);
      }
    }
    delay(20);
  }
#endif
}
