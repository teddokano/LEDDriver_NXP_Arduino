/** LED driver operation sample
 *  
 *  IMPORTANT!
 *  IMPORTANT!
 *  IMPORTANT!
 *    THIS SAMPLE CODE WORKS WITH "MsTimer2" LIBRARY.
 *    IMPORT "MsTimer2" in LibraryManager in Arduino-IDE or from https://playground.arduino.cc/Main/MsTimer2/
 *
 *  2 LED driver devices (PCA9956B) operated. 
 *  RGB LED color mixing. 
 *
 *  @author  Tedd OKANO
 *
 *  Released under the MIT license License
 */

#include <LEDDriver.h>
#include <MsTimer2.h>

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

PCA9956B ledd[] = { PCA9956B(0x02 >> 1), PCA9956B(0x04 >> 1) };
LED rgb[3][16] = {
  {
    LED(ledd + 0, 0),
    LED(ledd + 0, 3),
    LED(ledd + 0, 6),
    LED(ledd + 0, 9),
    LED(ledd + 0, 12),
    LED(ledd + 0, 15),
    LED(ledd + 0, 18),
    LED(ledd + 0, 21),
    LED(ledd + 1, 12),
    LED(ledd + 1, 15),
    LED(ledd + 1, 18),
    LED(ledd + 1, 21),
    LED(ledd + 1, 0),
    LED(ledd + 1, 3),
    LED(ledd + 1, 6),
    LED(ledd + 1, 9),
  },
  {
    LED(ledd + 0, 1),
    LED(ledd + 0, 4),
    LED(ledd + 0, 7),
    LED(ledd + 0, 10),
    LED(ledd + 0, 13),
    LED(ledd + 0, 16),
    LED(ledd + 0, 19),
    LED(ledd + 0, 22),
    LED(ledd + 1, 13),
    LED(ledd + 1, 16),
    LED(ledd + 1, 19),
    LED(ledd + 1, 22),
    LED(ledd + 1, 1),
    LED(ledd + 1, 4),
    LED(ledd + 1, 7),
    LED(ledd + 1, 10),
  },
  {
    LED(ledd + 0, 2),
    LED(ledd + 0, 5),
    LED(ledd + 0, 8),
    LED(ledd + 0, 11),
    LED(ledd + 0, 14),
    LED(ledd + 0, 17),
    LED(ledd + 0, 20),
    LED(ledd + 0, 23),
    LED(ledd + 1, 14),
    LED(ledd + 1, 17),
    LED(ledd + 1, 20),
    LED(ledd + 1, 23),
    LED(ledd + 1, 2),
    LED(ledd + 1, 5),
    LED(ledd + 1, 8),
    LED(ledd + 1, 11),
  }
};

void setup() {
  Serial.begin(9600);
  Serial.println("\n***** Hello, PCA9956B! *****");

  Wire.begin();
  ledd[0].begin(0.1, PCA9955B::ARDUINO_SHIELD);
  ledd[1].begin(0.1, PCA9955B::ARDUINO_SHIELD);
  ledd[0].buffer_enable(true);
  ledd[1].buffer_enable(true);

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
  static const int cycle = 50;
  static int count = 0;

  ledd[0].flush();
  ledd[1].flush();

  for (int color = 0; color < 3; color++) {
    for (int i = 0; i < 16; i++) {
      rgb[color][i] = pow(sin(PI * ((i / 16.0) + (color / 3.0) + (count / (float)cycle))), 4);
    }
  }
  count++;
  count %= cycle;
}
