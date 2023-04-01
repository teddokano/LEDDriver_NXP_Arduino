#include "SPI_device.h"

SPI_device::SPI_device()
{
	digitalWrite( SS, HIGH );
}

SPI_device::~SPI_device()
{
}

void SPI_device::txrx( uint8_t *data, int size )
{
	digitalWrite( SS, LOW );
	SPI.transfer( data, size );
	digitalWrite( SS, HIGH );
}
