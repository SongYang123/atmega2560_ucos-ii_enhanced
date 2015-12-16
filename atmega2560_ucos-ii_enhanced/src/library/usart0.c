#include "usart0.h"

char hexTable[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

#define usart0TxIntEnable()		UCSR0B |= ex(TXCIE0)
#define usart0TxIntDisable()	UCSR0B &= rex(TXCIE0)
#define usart0RxIntEnable()		UCSR0B |= ex(RXCIE0)
#define usart0RxIntDisable()	UCSR0B &= rex(RXCIE0)
#define usart0TxIntFlagClr()	UCSR0A |= ex(TXC0)

static char *usart0TxPtr;
static uint8 usart0TxCnt;
static OS_EVENT *usart0TxRdy;

static char usart0RxBuf[ex(UART0_RX_Q_SIZE)][ex(UART0_RX_SIZE)];
static uint8 usart0RxCnt;
static uint8 usart0RxQCnt;
static void *usart0RxQPtr[ex(UART0_RX_Q_SIZE)];
static OS_EVENT *usart0RxQ;

void usart0Init(void)
{
	UCSR0A = 0x02;
	UCSR0B = 0x18;
	UCSR0C = 0x06;
	UBRR0 = 207;

	usart0TxIntFlagClr();
	usart0TxIntEnable();
	usart0RxIntEnable();

	usart0TxRdy = OSSemCreate(0);
	usart0RxQ = OSQCreate(usart0RxQPtr, ex(UART0_RX_Q_SIZE));
	usart0RxCnt = 0;
	usart0RxQCnt = 0;
}

INT8U usart0Print(char *str)
{
	INT8U err;
	char temp;

	usart0TxPtr = str;
	usart0TxCnt = 0;
	temp = *str;
	if (temp != '\0') {
		UDR0 = temp;
		OSSemPend(usart0TxRdy, UART0_TX_TIMEOUT, &err);
	}
	return err;
}

INT8U usart0Hex8(uint8 hex8)
{
	char buffer[5];

	buffer[0] = '0';
	buffer[1] = 'x';
	buffer[2] = hexTable[(hex8 >> 4) & 0x0F];
	buffer[3] = hexTable[hex8 & 0x0F];
	buffer[4] = '\0';
	return usart0Print(buffer);
}

INT8U usart0Hex16(uint16 hex16)
{
	char buffer[7];

	buffer[0] = '0';
	buffer[1] = 'x';
	buffer[2] = hexTable[(hex16 >> 12) & 0x0F];
	buffer[3] = hexTable[(hex16 >> 8) & 0x0F];
	buffer[4] = hexTable[(hex16 >> 4) & 0x0F];
	buffer[5] = hexTable[hex16 & 0x0F];
	buffer[6] = '\0';
	return usart0Print(buffer);
}

INT8U usart0Hex32(uint32 hex32)
{
	char buffer[11];

	buffer[0] = '0';
	buffer[1] = 'x';
	buffer[2] = hexTable[(hex32 >> 28) & 0x0F];
	buffer[3] = hexTable[(hex32 >> 24) & 0x0F];
	buffer[4] = hexTable[(hex32 >> 20) & 0x0F];
	buffer[5] = hexTable[(hex32 >> 16) & 0x0F];
	buffer[6] = hexTable[(hex32 >> 12) & 0x0F];
	buffer[7] = hexTable[(hex32 >> 8) & 0x0F];
	buffer[8] = hexTable[(hex32 >> 4) & 0x0F];
	buffer[9] = hexTable[hex32 & 0x0F];
	buffer[10] = '\0';
	return usart0Print(buffer);
}

INT8U usart0LongInt(uint32 x)
{
	char digit[11];
	uint8 i;

	digit[10] = '\0';
	i = 9;
	do {
		digit[i] = '0' + x%10;
		x /= 10;
		i--;
	} while (x != 0);
	i++;
	return usart0Print(&digit[i]);
}

INT8U usart0Read(char **str)
{
	INT8U err;

	*str = (char *)OSQPend(usart0RxQ, UART0_RX_TIMEOUT, &err);
	return err;
}

static void usart0TxHandler(void)
{
	usart0TxCnt++;
	if (*(usart0TxPtr + usart0TxCnt) == 0) {
		OSIntEnter();
		OSSemPost(usart0TxRdy);
		OSIntExit();
	} else {
		UDR0 = usart0TxPtr[usart0TxCnt];
	}
}

static void usart0RxHandler(void)
{
	char usart0RxChar;

	usart0RxChar = UDR0;
	if (usart0RxChar == UART0_RX_EOF) {
		usart0RxBuf[usart0RxQCnt][usart0RxCnt] = '\0';
		usart0RxCnt = 0;
		OSIntEnter();
		OSQPost(usart0RxQ, usart0RxBuf[usart0RxQCnt]);
		usart0RxQCnt++;
		usart0RxQCnt &= ex(UART0_RX_Q_SIZE) - 1;
		OSIntExit();
	} else {
		usart0RxBuf[usart0RxQCnt][usart0RxCnt] = usart0RxChar;
		usart0RxCnt++;
		usart0RxCnt &= ex(UART0_RX_SIZE) - 1;
	}
}

ISR(USART0_TX_vect)
{
	usart0TxHandler();
}

ISR(USART0_RX_vect)
{
	usart0RxHandler();
}
