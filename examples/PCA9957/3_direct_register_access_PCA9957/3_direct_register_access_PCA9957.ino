/** PCA9957 LED driver operation sample
 *  
 *  This sample code is showing PCA9957 LED driver operation with direct register access.
 *  "write_r8()"" and "read_r8()"" can be used to write/read PCA9957 internal register. 
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
  ledd.begin(1.0, LEDDriver::ARDUINO_SHIELD);

  Serial.println("\n***** Hello, PCA9957! *****");
}

void loop() {
  for (int i = 0; i < 256; i += 8) {
    ledd.write_r8(PCA9957::PWM12, i);

    Serial.print("PCA9957 PWM12 register value = ");
    Serial.println(ledd.read_r8(PCA9957::PWM12), HEX);

    delay(100);
  }
}
