#ifndef _USART_H_
#define _USART_H_ 1

#define BAUDRATE 9600
#define BAUD_ASYNC_NORMAL (F_CPU/BAUDRATE/16-1)


void usart_init(const unsigned int ubrr);

void usart_putc(const char c);

void usart_puts(char *str);

char usart_getc();

#endif
