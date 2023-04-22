#include "LEDDriver.h"

/* PCA9956B class ******************************************/
PCA9956B::PCA9956B( uint8_t i2c_address ) : 
	PCA995x_I2C( i2c_address, 24, PCA9956B::PWM0, PCA9956B::IREF0, PCA9956B::IREFALL )
{
}

PCA9956B::~PCA9956B()
{
}

void PCA9956B::init( float current )
{
	uint8_t	init[]	= { 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA };
	reg_w( 0x80 | LEDOUT0, init, sizeof( init ) );
	write_r8( PWMALL, 0x00 );
	
	irefall( (uint8_t)(current * 255.0) );
}
