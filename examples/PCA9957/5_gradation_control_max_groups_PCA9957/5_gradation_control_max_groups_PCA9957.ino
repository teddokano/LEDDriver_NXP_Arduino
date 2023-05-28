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

  const float pwm_value = 1.0;  //  Default PWM output: 100%

  //  Defining channel to group relation
  const uint8_t channels[6][4] = {
    { 0, 3, 6, 9 },      //  Red LEDs
    { 1, 4, 7, 10 },     //  Green LEDs
    { 2, 5, 8, 11 },     //  Blue LEDs
    { 12, 13, 14, 18 },  //  White LEDs
    { 15, 16, 17, 19 },  //  White LEDs
    { 20, 21, 22, 23 },  //  White LEDs
  };

  //  Making GradationControl instances in an array
  GradationControl gradc[] = {
    GradationControl(&ledd, 0),
    GradationControl(&ledd, 1),
    GradationControl(&ledd, 2),
    GradationControl(&ledd, 3),
    GradationControl(&ledd, 4),
    GradationControl(&ledd, 5),
  };

  //  Number of groups gathered by colors
  int colors = sizeof(channels) / sizeof(channels[0]);

  //  Assigning channels into groups and set PWM output
  for (int c = 0; c < colors; c++) {
    for (uint32_t i = 0; i < sizeof(channels[c]); i++) {
      gradc[c].add_channel(channels[c][i]);  //  Assign a channel into a group
      ledd.pwm(channels[c][i], pwm_value);   //  Set PWM output
    }
  }

  gradc[0].set_gradation(1.0, 1.0, true, true, 0, 1.0);   //  peak current 100%, ramp-time 1 sec, ramp-up enabled, ramp-down enabled, hold-ON disabled, hold-OFF for 1 sec
  gradc[1].set_gradation(1.0, 1.0, true, true, 0, 1.0);   //  peak current 100%, ramp-time 1 sec, ramp-up enabled, ramp-down enabled, hold-ON disabled, hold-OFF for 1 sec
  gradc[2].set_gradation(1.0, 1.0, true, true, 0, 1.0);   //  peak current 100%, ramp-time 1 sec, ramp-up enabled, ramp-down enabled, hold-ON disabled, hold-OFF for 1 sec
  gradc[3].set_gradation(1.0, 3.0, false, true, 0, 1.0);  //  peak current 100%, ramp-time 3 sec, ramp-up disabled, ramp-down enabled, hold-ON disabled, hold-OFF for 1 sec
  gradc[4].set_gradation(1.0, 3.0, false, true, 0, 1.0);  //  peak current 100%, ramp-time 3 sec, ramp-up disabled, ramp-down enabled, hold-ON disabled, hold-OFF for 1 sec
  gradc[5].set_gradation(1.0, 3.0, false, true, 0, 1.0);  //  peak current 100%, ramp-time 3 sec, ramp-up disabled, ramp-down enabled, hold-ON disabled, hold-OFF for 1 sec

  //  Get calculated cycle period (in second)
  float cycle = gradc[0].cycle;

  //  Start groups from 0 to 2
  for (int i = 0; i < 3; i++) {
    gradc[i].start();
    delay((cycle / 3) * 1000);
  }

  //  Get calculated cycle period (in second)
  cycle = gradc[3].cycle;

  //  Start groups from 3 to 5
  for (int i = 3; i < 6; i++) {
    gradc[i].start();
    delay((cycle / 3) * 1000);
  }
}

void loop() {
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