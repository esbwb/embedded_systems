#ifndef _USART_H_
#define _USART_H_ 1

#ifdef WITH_STDIO
#include <stdio.h>
#define usart_printf(fmt, ...) printf(fmt, __VA_ARGS__)
#else
#define usart_printf(fmt, ...)
#endif 

void usart_init();

void usart_putc(const char c);

void usart_puts(char *str);

char usart_getc();

#endif
