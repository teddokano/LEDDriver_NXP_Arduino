#ifndef ARDUINO_GRADATION_CONTROL_NXP_ARD_H
#define ARDUINO_GRADATION_CONTROL_NXP_ARD_H

#include <LEDDriver.h>

class GradationControl
{
public:
	enum control : int
	{
		STOP,
		DUMMY,
		ONE_SHOT,
		CONTINUOUS,
	};
	
	float	cycle;

	GradationControl( PCA995x* devp, int num_group, uint32_t bitmap = 0x0000 );
	virtual ~GradationControl();

	float set_gradation( float max_iref, float time, bool up = true, bool down = true, float on = 0.0, float off = 0.0 );
	void gradation_group_assign( uint32_t bitmap );
	void add_channel( uint8_t ch );
	void gradation_channel_enable( uint32_t bitmap );
	
	void control( int ctrl );
	void start( bool continuous = true );
	void stop( void );
	
private:
	PCA995x* devp;
	const int	group;
	static const float	HOLDTIME[];
};

#endif //	ARDUINO_GRADATION_CONTROL_NXP_ARD_H
