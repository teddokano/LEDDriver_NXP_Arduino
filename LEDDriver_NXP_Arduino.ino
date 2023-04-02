/** PCA9957 LED driver operation sample
 *  
 *  This sample code is showing PCA9957 LED driver operation with direct register access.
 *  write_r8() and read_r8() can be used to write/read PCA9957 internal register. 
 *
 *  @author  Tedd OKANO
 *
 *  Released under the MIT license License
 *
 *  About PCA9957:
 *    https://www.nxp.jp/products/power-management/lighting-driver-and-controller-ics/led-drivers/24-channel-spi-serial-bus-32-ma-5-5-v-constant-current-led-driver:PCA9957
 */

void setup() {
  SPI.begin();
  Serial.begin(9600);
  Serial.println("\r***** Hello, PCA9955B! *****");

  ledd.begin(0.1, PCA9957::ARDUINO_SHIELD);
}

void loop() {
  int cycle = 60;
  float pwm;

  int n_ch = ledd.n_channel;
  int ch;
  float v[n_ch];
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
