/** PCA9957 LED driver operation sample
 *  
 *  This sample code is showing PCA9957 LED driver operation with PWM value setting change.
 *  "The ledd.pwm() takes channel number and PWM ratio. 
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
  pinMode(SS, OUTPUT);  //  Required for UNO R4
  
  ledd.begin(1.0, PCA9957::ARDUINO_SHIELD);

  Serial.println("\n***** Hello, PCA9957! *****");
}

void loop() {
  ledd.pwm(0, 1.0);
  Serial.println("ON ");
  delay(100);

  ledd.pwm(0, 0.0);
  Serial.println("OFF");
  delay(100);
}
