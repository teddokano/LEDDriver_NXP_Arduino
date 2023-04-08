/** PCA9955B operation sample
 *  
 *  This sample code is to show how the device can be operated without the LED driver library
 *
 *  @author  Tedd OKANO
 *
 *  Released under the MIT license License
 *
 *  About PCA9955B:
 *    https://www.nxp.com/products/power-management/lighting-driver-and-controller-ics/led-drivers/16-channel-fm-plus-ic-bus-57-ma-20-v-constant-current-led-driver:PCA9955BTW
 */

#include <Wire.h>

enum reg_num {
	MODE1, MODE2, 
	LEDOUT0, LEDOUT1, LEDOUT2, LEDOUT3, 
	GRPPWM, GRPFREQ, 
	PWM0,  PWM1,  PWM2,   PWM3,   PWM4,   PWM5,   PWM6,   PWM7, 
	PWM8,  PWM9,  PWM10,  PWM11,  PWM12,  PWM13,  PWM14,  PWM15, 
	IREF0, IREF1, IREF2,  IREF3,  IREF4,  IREF5,  IREF6,  IREF7, 
	IREF8, IREF9, IREF10, IREF11, IREF12, IREF13, IREF14, IREF15, 
	RAMP_RATE_GRP0, STEP_TIME_GRP0, HOLD_CNTL_GRP0, IREF_GRP0, 
	RAMP_RATE_GRP1, STEP_TIME_GRP1, HOLD_CNTL_GRP1, IREF_GRP1, 
	RAMP_RATE_GRP2, STEP_TIME_GRP2, HOLD_CNTL_GRP2, IREF_GRP2, 
	RAMP_RATE_GRP3, STEP_TIME_GRP3, HOLD_CNTL_GRP3, IREF_GRP3, 
	GRAD_MODE_SEL0, GRAD_MODE_SEL1, 
	GRAD_GRP_SEL0, GRAD_GRP_SEL1, GRAD_GRP_SEL2, GRAD_GRP_SEL3, 
	GRAD_CNTL, 
	OFFSET, 
	SUBADR1, SUBADR2, SUBADR3, ALLCALLADR, 
	PWMALL, IREFALL, 
	EFLAG0, EFLAG1, EFLAG2, EFLAG3, 
};

enum incremental_access {
  NONE,
  INCREMENTAL = 0x80
};

#define TARGET_ADDRESS (0xBC >> 1)

int i2c_tx(uint8_t i2c_addr, uint8_t *data, int size, bool stop = true);
int i2C_rx(uint8_t i2c_addr, uint8_t *data, int size);
int i2c_reg_w(uint8_t i2c_addr, reg_num reg, uint8_t data);
int i2c_reg_r(uint8_t i2c_addr, reg_num reg, uint8_t *data, int size);
uint8_t i2c_reg_r(uint8_t i2c_addr, reg_num reg);

void i2c_write_r8(uint8_t i2c_addr, reg_num reg, uint8_t val);
uint8_t i2c_read_r8(uint8_t i2c_addr, reg_num reg);

void setup() {
  // Start to use I2C as host
  Wire.begin();

  //  Initialize PCA9955B registers
  uint8_t ledout[] = { 0xAA, 0xAA, 0xAA, 0xAA };
  i2c_reg_w(INCREMENTAL | TARGET_ADDRESS, LEDOUT0, ledout, sizeof(ledout));  //  Set all channels are ready to PWM output by writing LEDOUT0 ~ LEDOUT3 registers by auto-increemnt access
  i2c_write_r8(TARGET_ADDRESS, PWMALL, 0x00);                                //  Set PWM as 0% for all channels
  i2c_write_r8(TARGET_ADDRESS, IREFALL, 0xFF);                               //  Set output current as 100% for all channels

  // Force OE (Output enable) pin LOW. Arduino "D8" pin is tied to PCA9955B's OE pin
  pinMode(8, OUTPUT);
  digitalWrite(8, 0);

  //  Enabling Serial output and showing "Hello message"
  Serial.begin(9600);
  Serial.println("\r***** Hello, PCA9955B! *****");
}

void loop() {
  for (int channel = 0; channel < 16; channel++) {
    for (int brightness = 0; brightness < 256; brightness++) {
      i2c_write_r8(TARGET_ADDRESS, (reg_num)(PWM0 + channel), brightness);
      delay(1);
    }
    for (int brightness = 0; brightness < 256; brightness++) {
      i2c_write_r8(TARGET_ADDRESS, (reg_num)(PWM0 + channel), 255 - brightness);
      delay(1);
    }
  }
}

int i2c_tx(uint8_t i2c_addr, uint8_t *data, int size, bool stop) {
  Wire.beginTransmission(i2c_addr);
  size = Wire.write(data, size);
  uint8_t rtn = Wire.endTransmission(stop);

  if (rtn)
    Serial.println("i2c_tx: ERROR");

  return size;
}

int i2C_rx(uint8_t i2c_addr, uint8_t *data, int size) {
  int r_size = Wire.requestFrom(i2c_addr, (uint16_t)size);

  if (r_size != size)
    Serial.println("i2c_rx: received size was shorter than specified");

  for (int i = 0; i < size; i++) {
    while (!Wire.available())
      ;
    data[i] = Wire.read();
  }
  return r_size;
}

int i2c_reg_w(uint8_t i2c_addr, reg_num reg, uint8_t *data, int size) {
  uint8_t buffer[size + 1];

  buffer[0] = reg;
  for (int i = 0; i < size; i++)
    buffer[i + 1] = data[i];

  return i2c_tx(i2c_addr, buffer, sizeof(buffer));
}

int i2c_reg_w(uint8_t i2c_addr, reg_num reg, uint8_t data) {
  uint8_t buffer[2];

  buffer[0] = reg;
  buffer[1] = data;

  return i2c_tx(i2c_addr, buffer, sizeof(buffer));
}

int i2c_reg_r(uint8_t i2c_addr, reg_num reg, uint8_t *data, int size) {
  uint8_t r = reg;
  i2c_tx(i2c_addr, &r, 1, false);
  return i2C_rx(i2c_addr, data, size);
}

uint8_t i2c_reg_r(uint8_t i2c_addr, reg_num reg) {
  uint8_t r = reg;
  uint8_t buffer;

  i2c_tx(i2c_addr, &r, 1, false);
  i2C_rx(i2c_addr, &buffer, 1);
  return buffer;
}

void i2c_write_r8(uint8_t i2c_addr, reg_num reg, uint8_t val) {
  i2c_reg_w(i2c_addr, reg, val);
}

uint8_t i2c_read_r8(uint8_t i2c_addr, reg_num reg) {
  return i2c_reg_r(i2c_addr, reg);
}
