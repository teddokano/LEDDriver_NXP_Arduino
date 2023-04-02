/** PCA9956B LED driver operation sample
 *  
 *  This sample code is showing PCA9956B LED driver operation with direct register access.
 *  "write_r8()"" and "read_r8()"" can be used to write/read PCA9956B internal register. 
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
  Serial.println("\n***** Hello, PCA9956B *****");

  Wire.begin();
  ledd.begin(1.0, PCA9956B::ARDUINO_SHIELD);
}

void loop() {
  for (int i = 0; i < 256; i += 8) {
    ledd.write_r8(PCA9956B::PWM12, i);

    Serial.print("PCA9956B PWM12 register value = ");
    Serial.println(ledd.read_r8(PCA9956B::PWM12), HEX);

    delay(100);
  }
}
