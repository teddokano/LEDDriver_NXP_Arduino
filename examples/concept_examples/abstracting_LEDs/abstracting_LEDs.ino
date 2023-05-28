/** LED driver operation sample
 *  
 *  Showing abstraction approach to manage multiple LEDs easy. 
 *  Which this "LED class", each LEDs can be grouped and indexed arbitrary, independent from LED driver devices. 
 *  This sample is using LED class to set PWM ratio by simple assignment. 
 *
 *  @author  Tedd OKANO
 *
 *  Released under the MIT license License
 */

#include <PCA9955B.h>
#include <LED.h>

PCA9955B ledd;

LED led[] = {
  LED(&ledd, 0), LED(&ledd, 1), LED(&ledd, 2), LED(&ledd, 3),
  LED(&ledd, 4), LED(&ledd, 5), LED(&ledd, 6), LED(&ledd, 7),
  LED(&ledd, 8), LED(&ledd, 9), LED(&ledd, 10), LED(&ledd, 11),
  LED(&ledd, 12), LED(&ledd, 13), LED(&ledd, 14), LED(&ledd, 15)
};

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;

  Wire.begin();
  ledd.begin(0.1, PCA9955B::ARDUINO_SHIELD);

  Serial.println("\n***** Hello, PCA9955B! *****");
}

void loop() {
  led[0] = led[3] = led[6] = 1.0;
  led[1] = led[4] = led[7] = 0.0;
  led[2] = led[5] = led[8] = 0.0;
  delay(100);

  led[0] = led[3] = led[6] = 0.0;
  led[1] = led[4] = led[7] = 1.0;
  led[2] = led[5] = led[8] = 0.0;
  delay(100);

  led[0] = led[3] = led[6] = 0.0;
  led[1] = led[4] = led[7] = 0.0;
  led[2] = led[5] = led[8] = 1.0;
  delay(100);
}
