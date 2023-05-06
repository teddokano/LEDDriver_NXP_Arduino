/** PCA9955B LED driver operation sample
 *  
 *  This sample code is showing PCA9955B LED driver operation with Gradation Control.
 *
 *  @author  Tedd OKANO
 *
 *  Released under the MIT license License
 *
 *  About PCA9955B:
 *    https://www.nxp.com/products/power-management/lighting-driver-and-controller-ics/led-drivers/24-channel-spi-serial-bus-32-ma-5-5-v-constant-current-led-driver:PCA9957
 */

#include <PCA9955B.h>
#include <GradationControl.h>

PCA9955B ledd;

void setup() {
  Serial.begin(9600);
  Serial.println("\n***** Hello, PCA9955B! *****");

  Wire.begin();
  ledd.begin(1.0, PCA9955B::ARDUINO_SHIELD);

  const float pwm_value = 1.0;  //  Default PWM output: 100%

  //  Defining channel to group relation for group 0 to 2
  const uint8_t rgb_leds[3][3] = {
    { 0, 3, 6 },  //  Red LEDs
    { 1, 4, 7 },  //  Green LEDs
    { 2, 5, 8 },  //  Blue LEDs
  };

  //  Defining channel to group relation for group 3
  const uint8_t white_leds[] = { 9, 10, 11, 12, 13, 14, 15 };  //  White LEDs

  //  Making GradationControl instances in an array
  GradationControl gradc[] = {
    GradationControl(&ledd, 0),
    GradationControl(&ledd, 1),
    GradationControl(&ledd, 2),
    GradationControl(&ledd, 3),
  };

  //  Assigning channels into groups and set PWM output
  for (int c = 0; c < 3; c++) {
    for (uint32_t i = 0; i < sizeof(rgb_leds[c]); i++) {
      gradc[c].add_channel(rgb_leds[c][i]);  //  Assign a channel into a group
      ledd.pwm(rgb_leds[c][i], pwm_value);   //  Set PWM output
    }
  }

  for (uint32_t i = 0; i < sizeof(white_leds); i++) {
    gradc[3].add_channel(white_leds[i]);  //  Assign a channel into a group
    ledd.pwm(white_leds[i], pwm_value);   //  Set PWM output
  }

  gradc[0].set_gradation(1.0, 1.0, true, true, 0, 1.0);   //  peak current 100%, ramp-time 1 sec, ramp-up enabled, ramp-down enabled, hold-ON disabled, hold-OFF for 1 sec
  gradc[1].set_gradation(1.0, 1.0, true, true, 0, 1.0);   //  peak current 100%, ramp-time 1 sec, ramp-up enabled, ramp-down enabled, hold-ON disabled, hold-OFF for 1 sec
  gradc[2].set_gradation(1.0, 1.0, true, true, 0, 1.0);   //  peak current 100%, ramp-time 1 sec, ramp-up enabled, ramp-down enabled, hold-ON disabled, hold-OFF for 1 sec
  gradc[3].set_gradation(1.0, 3.0, false, true, 0, 1.0);  //  peak current 100%, ramp-time 3 sec, ramp-up disabled, ramp-down enabled, hold-ON disabled, hold-OFF for 1 sec

  //  Get calculated cycle period (in second)
  float cycle = gradc[0].cycle;

  //  Start groups from 0 to 2
  for (int i = 0; i < 3; i++) {
    gradc[i].start();
    delay((cycle / 3) * 1000);
  }

  gradc[3].start();
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