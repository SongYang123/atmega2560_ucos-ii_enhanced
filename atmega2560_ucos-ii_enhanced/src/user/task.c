#include "task.h"

void blink(void *pdata)
{
	(void)pdata;
	while (1) {
		ledOn();
		OSTimeDly(1);
		ledOff();
		OSTimeDly(29);
		ledOn();
		OSTimeDly(1);
		ledOff();
		OSTimeDly(219);
	}
}

void serial(void *pdata)
{
	char *str;

	(void)pdata;
	while (1) {
		usart0Read(&str);
		usart0Print(str);
	}
}
