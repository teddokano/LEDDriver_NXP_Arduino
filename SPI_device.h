/** SPI device abstracting class
 *
 *	This class provides common methods for all SPI devices
 *
 *  @class   SPI_device
 *  @author  Tedd OKANO
 *
 *  Released under the MIT license License
 */

#ifndef ARDUINO_SPI_DEVICE_H
#define ARDUINO_SPI_DEVICE_H

#include <Arduino.h>
#include <stdint.h>
#include <SPI.h>

class SPI_device
{
public:
	/** Create a SPI_device
     */
	SPI_device();

    /** Destructor of SPI_device
     */
    ~SPI_device();
	
	/** Send data
	 * 
	 * @param data pointer to data buffer
	 * @param size data size
	 * @return transferred data size
	 */
	void txrx( uint8_t *data, uint16_t size );

	/** Multiple register write
	 * 
	 * @param reg register index/address/pointer
	 * @param data pointer to data buffer
	 * @param size data size
	 */
	void reg_access( uint8_t reg_adr, uint8_t *data, uint16_t size );

	/** Single register write
	 * 
	 * @param reg register index/address/pointer
	 * @param data pointer to data buffer
	 * @param size data size
	 */
	uint8_t reg_access( uint8_t reg_adr, uint8_t data );
};

#endif //	ARDUINO_SPI_DEVICE_H
