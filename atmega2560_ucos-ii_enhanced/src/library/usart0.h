#ifndef __USART0_H__
#define __USART0_H__

#include "define.h"

#define UART0_TX_TIMEOUT		0xFFFFFFFF

#define UART0_RX_TIMEOUT		0xFFFFFFFF
#define UART0_RX_EOF			'\r'

/* queue size is 2 ^ UART0_RX_Q_SIZE */
#define UART0_RX_Q_SIZE			2
/* buffer size is 2 ^ UART0_RX_SIZE */
#define UART0_RX_SIZE			4

void usart0Init(void);

INT8U usart0Print(char *str);
INT8U usart0Hex8(uint8 hex8);
INT8U usart0Hex16(uint16 hex16);
INT8U usart0Hex32(uint32 hex32);
INT8U usart0LongInt(uint32 x);

INT8U usart0Read(char **str);

#endif
