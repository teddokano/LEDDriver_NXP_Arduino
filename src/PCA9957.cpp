#include "LEDDriver.h"

/* PCA9957 class ******************************************/
PCA9957::PCA9957() : 
	PCA995x_SPI( 24, PCA9957::PWM0, PCA9957::IREF0, PCA9957::IREFALL )
{
}

PCA9957::~PCA9957()
{
}

void PCA9957::init( float current )
{
	uint8_t	init[]	= { 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA };

	digitalWrite( SS, HIGH );

	write_r8( MODE2,  0x18 );
	write_r8( PWMALL, 0x00 );
	reg_w( LEDOUT0, init, sizeof( init ) );
	
	irefall( (uint8_t)(current * 255.0) );
	
}



