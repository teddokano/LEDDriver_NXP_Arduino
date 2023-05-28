/** PCA9957 LED driver operation sample
 *  
 *  This sample code is showing PCA9957 LED driver operation with Gradation Control.
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
  while (!Serial)
    ;

  SPI.begin();
  ledd.begin(1.0, PCA9957::ARDUINO_SHIELD);

  Serial.println("\n***** Hello, PCA9957! *****");

  GradationControl gradcR = GradationControl(&ledd, 0); //  Gradation group 0
  GradationControl gradcB = GradationControl(&ledd, 1); //  Gradation group 1
  gradcR.add_channel(0);  //  Assign channel 0 to group 0
  gradcB.add_channel(5);  //  Assign channel 5 to group 1
  ledd.pwm(0, 1.0);       //  Set PWM output
  ledd.pwm(5, 1.0);       //  Set PWM output

  gradcR.set_gradation(1.0, 1.0); //  Set peak current to 100% and ramp-time to 1.0 second
  gradcB.set_gradation(1.0, 1.0); //  Set peak current to 100% and ramp-time to 1.0 second

  gradcR.start();         //  Start group 0
  delay(1000);            //  After 1 second
  gradcB.start();         //  Start group 1
}

void loop() {
  //  do nothing from MCU
}
