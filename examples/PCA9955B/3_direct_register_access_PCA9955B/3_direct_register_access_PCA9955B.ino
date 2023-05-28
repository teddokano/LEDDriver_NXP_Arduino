/** PCA9955B LED driver operation sample
 *  
 *  This sample code is showing PCA9955B LED driver operation with direct register access.
 *  "write_r8()"" and "read_r8()"" can be used to write/read PCA9955B internal register. 
 *
 *  @author  Tedd OKANO
 *
 *  Released under the MIT license License
 *
 *  About PCA9955B:
 *    https://www.nxp.com/products/power-management/lighting-driver-and-controller-ics/led-drivers/16-channel-fm-plus-ic-bus-57-ma-20-v-constant-current-led-driver:PCA9955BTW
 */

#include <PCA9955B.h>

PCA9955B ledd;

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;

  Wire.begin();
  ledd.begin(1.0, PCA9955B::ARDUINO_SHIELD);

  Serial.println("\n***** Hello, PCA9955B *****");
}

void loop() {
  for (int i = 0; i < 256; i += 8) {
    ledd.write_r8(PCA9955B::PWM12, i);

    Serial.print("PCA9955B PWM12 register value = ");
    Serial.println(ledd.read_r8(PCA9955B::PWM12), HEX);

    delay(100);
  }
}
