/** PCA9955B LED driver operation sample
 *  
 *  This sample code is showing PCA9955B LED driver operation with Gradation Control.
 *
 *  @author  Tedd OKANO
 *
 *  Released under the MIT license License
 *
 *  About PCA9955B:
 *    https://www.nxp.com/products/power-management/lighting-driver-and-controller-ics/led-drivers/16-channel-fm-plus-ic-bus-57-ma-20-v-constant-current-led-driver:PCA9955BTW
 */

#include <PCA9955B.h>
#include <GradationControl.h>

PCA9955B ledd;

void setup() {
  Serial.begin(9600);
  Serial.println("\n***** Hello, PCA9955B! *****");

  Wire.begin();
  ledd.begin(1.0, PCA9955B::ARDUINO_SHIELD);

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
