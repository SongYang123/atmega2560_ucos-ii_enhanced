#include "basic.h"

void enablePullup(void)
{
	MCUCR &= rex(PUD);
}

void disablePullup(void)
{
	MCUCR |= ex(PUD);
}

void ledInit(void)
{
	DDRB |= ex(7);
}

void ledOn(void)
{
	PORTB |= ex(7);
}

void ledOff(void)
{
	PORTB &= rex(7);
}
