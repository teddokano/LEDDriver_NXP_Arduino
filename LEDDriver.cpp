#include "LEDDriver.h"

/* LEDDriver class ******************************************/

LEDDriver::LEDDriver( uint8_t n_ch, uint8_t PWM_r ) : n_channel( n_ch ), reg_PWM( PWM_r )
{
	//  do nothing.
	//  leave it in default state.
}

LEDDriver::~LEDDriver()
{
}

void LEDDriver::pwm( uint8_t ch, float value )
{
	reg_access( reg_PWM + ch, (uint8_t)(value * 255.0) );
}

void LEDDriver::pwm( float* values )
{
	uint8_t	v[ n_channel ];
	for ( int i = 0; i < n_channel; i++ )
		v[ i ]	= (uint8_t)(values[ i ] * 255.0);

	reg_access( 0x80 | reg_PWM, v, n_channel );
}



/* PCA995x class ******************************************/

PCA995x::PCA995x( uint8_t n_ch, uint8_t PWM_r, uint8_t IREF_r, uint8_t IREFALL_r ) : 
	LEDDriver( n_ch, PWM_r ), reg_IREF( IREF_r ), reg_IREFALL( IREFALL_r )
{
	//  do nothing.
	//  leave it in default state.
}

PCA995x::~PCA995x()
{
}

void PCA995x::begin( float current, board env )
{
	init( current );
	
	if ( env ) {
		pinMode( 8, OUTPUT );
		digitalWrite( 8 , 0 );
	}
}

void PCA995x::irefall( uint8_t iref )
{
	reg_access( reg_IREFALL, iref );
}



/* PCA995x_I2C class ******************************************/

PCA995x_I2C::PCA995x_I2C( uint8_t i2c_address, uint8_t n_ch, uint8_t PWM_r, uint8_t IREF_r, uint8_t IREFALL_r ) : 
	PCA995x( n_ch, PWM_r, IREF_r, IREFALL_r ), 
	I2C_device( i2c_address )
{
	//  do nothing.
	//  leave it in default state.
}

PCA995x_I2C::~PCA995x_I2C()
{
}

void PCA995x_I2C::reg_access( uint8_t reg, uint8_t val  )
{
	write_r8( reg, val );
}
void PCA995x_I2C::reg_access( uint8_t reg, uint8_t *vp, uint8_t len )
{
	reg_w( 0x80 | reg, vp, len );
}



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
	
	irefall( (uint8_t)(current * 255.0) );
}

/* PCA9956B class ******************************************/
PCA9956B::PCA9956B( uint8_t i2c_address ) : 
	PCA995x_I2C( i2c_address, 24, PCA9956B::PWM0, PCA9956B::IREF0, PCA9955B::IREFALL )
{
}

PCA9956B::~PCA9956B()
{
}

void PCA9956B::init( float current )
{
	uint8_t	init[]	= { 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA };
	reg_w( 0x80 | LEDOUT0, init, sizeof( init ) );
	
	irefall( (uint8_t)(current * 255.0) );
}
