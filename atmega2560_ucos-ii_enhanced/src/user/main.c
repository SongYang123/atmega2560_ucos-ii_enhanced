#include "user.h"

static OS_STK stack0[128];
static OS_STK stack1[128];

static void tickInit(void)
{
	TCNT1 = 0;
	OCR1A = 249;
	OCR1B = 0;
	TCCR1A = 0x00;
	TCCR1B = 0x0C;
	TCCR1C = 0x00;
	TIFR1 = ex(OCF1A);
	TIMSK1 = ex(OCIE1A);
}

int main(void)
{
	cli();
	OSInit();
	tickInit();

	enablePullup();
	usart0Init();

	ledInit();

	OSTaskCreate(serial, (void *)0, &stack0[127], 0);
	OSTaskCreate(blink, (void *)0, &stack1[127], 1);

	OSStart();

	return 0;
}
