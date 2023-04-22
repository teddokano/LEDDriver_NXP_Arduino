#include "LEDDriver.h"

/* PCA9955B class ******************************************/
PCA9955B::PCA9955B( uint8_t i2c_address ) : 
	PCA995x_I2C( i2c_address, 16, PCA9955B::PWM0, PCA9955B::IREF0, PCA9955B::IREFALL )
{
}

PCA9955B::~PCA9955B()
{
}

void PCA9955B::init( float current )
{
	uint8_t	init[]	= { 0xAA, 0xAA, 0xAA, 0xAA };
	reg_w( 0x80 | LEDOUT0, init, sizeof( init ) );
	write_r8( PWMALL, 0x00 );
	
	irefall( (uint8_t)(current * 255.0) );
}
