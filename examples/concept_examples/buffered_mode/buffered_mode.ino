/** LED driver operation sample
 *  
 *  Showing "buffered mode" of LEDDriver library. 
 *  The LEDDriver has mode of "unbuffered" (default) and "buffered". 
 *  
 *  The "unbuffered" mode is a simple mode, the device PWM output is changed each time of "pwm()" method call. 
 *  It means, the MCU and LED driver device data transfer is done each time. 
 *
 *  The "buffered" mode is made to supress redundant data transfer between MCU and LED driver. 
 *  The "pwm()" method call updates library internal data buffer only. The transfer happens only when "flush()" methos is called. 
 *
 *  This sample code is showing the operation conjunction with the "LED class" which was demonstrated in "concept_examples/abstracting_LEDs" sample code. 
 *  In this sample, the LEDs are grouped re-indexed by using the LED class. 
 *
 *  @author  Tedd OKANO
 *
 *  Released under the MIT license License
 */

#include <LEDDriver.h>

/** Advanced abstraction layer for easy LED management
 *  @class  LED
 */

class LED {
public:
  LED(LEDDriver* leddp, int ch) {
    devp = leddp;
    channel = ch;
  }
  float operator=(float v) {
    devp->pwm(channel, v);
    return v;
  }
private:
  LEDDriver* devp;
  int channel;
};

PCA9955B ledd;
LED rgb[3][3] = {
  { LED(&ledd, 0), LED(&ledd, 3), LED(&ledd, 6) },
  { LED(&ledd, 1), LED(&ledd, 4), LED(&ledd, 7) },
  { LED(&ledd, 2), LED(&ledd, 5), LED(&ledd, 8) }
};
LED white[] = {  //  re-ordered to match physical alignment
  LED(&ledd, 9), LED(&ledd, 11), LED(&ledd, 12), LED(&ledd, 13),
  LED(&ledd, 10), LED(&ledd, 14), LED(&ledd, 15)
};

void setup() {
  Serial.begin(9600);
  Serial.println("\n***** Hello, PCA9955B! *****");

  Wire.begin();
  ledd.begin(0.01, PCA9955B::ARDUINO_SHIELD);
  ledd.buffer_enable(true);
}

const int interval = 20;
const int cycle = 150;
int count = 0;

void loop() {
  //  RGB LED control
  for (int color = 0; color < 3; color++) {
    rgb[color][0] = rgb[color][1] = rgb[color][2] = 0.5 - 0.5 * cos(2 * PI * ((cycle * color / 3.0) + count) / (float)cycle);
  }

  //  WHITE LED control
  for (int white_index = 0; white_index < 7; white_index++) {
    white[white_index] = 0.5 - 0.5 * cos(2 * PI * ((cycle * white_index / 7.0) + count) / (float)cycle);
  }

  ledd.flush();

  count++;
  count %= cycle;

  delay(interval);
}
