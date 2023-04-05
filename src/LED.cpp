#include "LED.h"

LED::LED( LEDDriver* leddp, int ch )
{
	devp = leddp;
	channel = ch;
}

float LED::operator=( float v )
{
	devp->pwm(channel, v);
	return v;
}
