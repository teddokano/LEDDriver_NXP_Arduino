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
#include <GradationControl.h>

PCA9957 ledd;

void setup() {
  Serial.begin(9600);
  Serial.println("\n***** Hello, PCA9957! *****");

  SPI.begin();
  ledd.begin(1.0, PCA9957::ARDUINO_SHIELD);
  GradationControl gradc0 = GradationControl(&ledd, 0, 0x049);
  GradationControl gradc1 = GradationControl(&ledd, 1, 0x92);
  GradationControl gradc2 = GradationControl(&ledd, 2, 0x124);

  /*
    ledd.pwm(0, 1.0);
  ledd.pwm(3, 1.0);
  ledd.pwm(6, 1.0);
*/
  ledd.pwm(1, 1.0);
  ledd.pwm(4, 1.0);
  ledd.pwm(7, 1.0);
  
  ledd.pwm(2, 1.0);
  ledd.pwm(5, 1.0);
  ledd.pwm(8, 1.0);
  
  //gradc0.set_gradation(1.0, 2.0);
  gradc1.set_gradation(1.0, 1.0);
  gradc2.set_gradation(1.0, 0.5);
  
  gradc0.start();
// gradc1.start();
  gradc2.start();

  dump();
}

void loop() {
//  ledd.pwm(23, 1.0);
//  Serial.println("ON ");
  delay(1000);

//  ledd.pwm(23, 0.0);
//  Serial.println("OFF");
  delay(1000);
}

void dump() {
#define N 0x69
  uint8_t r[N];
  for (int i = 0; i < N; i++) {
    r[i] = ledd.read_r8(i);
  }

  for (int i = 0; i < N; i++) {
    Serial.print(i, HEX);
    Serial.print(" : ");
    Serial.println(r[i], HEX);
  }
}