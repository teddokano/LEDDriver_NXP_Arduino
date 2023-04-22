/** LED driver operation sample
 *  
 *  IMPORTANT!
 *  IMPORTANT!
 *  IMPORTANT!
 *    THIS SAMPLE CODE WORKS WITH "MsTimer2" LIBRARY.
 *    IMPORT "MsTimer2" in LibraryManager in Arduino-IDE or from https://playground.arduino.cc/Main/MsTimer2/
 *
 *  With timer library, the LED refresh rate can be managed easily. 
 *  This sample is showing how the timer library can be used with LEDDriver buffer mode. 
 *
 *  @author  Tedd OKANO
 *
 *  Released under the MIT license License
 */

#include <PCA9955B.h>
#include <LED.h>
#include <MsTimer2.h>

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
  ledd.begin(0.1, PCA9955B::ARDUINO_SHIELD);
  ledd.buffer_enable(true);

  MsTimer2::set(20, timer_callback);
  MsTimer2::start();
}

bool tim_flag = false;

void timer_callback() {
  tim_flag = true;
}

void loop() {
  if (tim_flag) {
    tim_flag = false;
    LED_update();
  }
}

void LED_update(void) {
  static const int cycle = 150;
  static int count = 0;

  ledd.flush();

  //  RGB LED control
  for (int color = 0; color < 3; color++) {
    rgb[color][0] = rgb[color][1] = rgb[color][2] = 0.5 - 0.5 * cos(2 * PI * ((cycle * color / 3.0) + count) / (float)cycle);
  }

  //  WHITE LED control
  for (int white_index = 0; white_index < 7; white_index++) {
    white[white_index] = 0.5 - 0.5 * cos(2 * PI * ((cycle * white_index / 7.0) + count) / (float)cycle);
  }

  count++;
  count %= cycle;
}
