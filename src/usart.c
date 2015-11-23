#include <avr/io.h>

#define BAUD 9600
#include <util/setbaud.h>

#include "usart.h"
#include "macros.h"

#ifdef WITH_STDIO
static int usart_getc_stdio(FILE * UNUSED(file))
{
	return usart_getc();
}

static int usart_putc_stdio(char c, FILE * UNUSED(file))
{
	usart_putc(c);
	return 0;
}
#endif

void usart_init()
{
        /* Write high byte of baud rate to ubrr */
        UBRR0H = UBRRH_VALUE;
        /* Write low byte of baud rate to ubrr */
        UBRR0L = UBRRL_VALUE;

	#if USE_2X
	UCSR0A |= (1<<U2X0);
	#else
	UCSR0A &= ~(1<<U2X0);
	#endif

        /* Enable receiver and transmitter */
        UCSR0B = (1<<RXEN0) | (1<<TXEN0);

        /* Set frame format to 8n1 */
        UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);

	#ifdef WITH_STDIO
	/* This opens stdout/stderr for writing to usart
	   and stdin for reading from usart */
	fdevopen(usart_putc_stdio, usart_getc_stdio);
	#endif
}

char usart_getc()
{
        while (!(UCSR0A & (1<<RXC0)));

        return (char) UDR0;
}

void usart_putc(const char c)
{
        while (!(UCSR0A & (1<<UDRE0)));

        UDR0 = (unsigned char) c;
}

void usart_puts(char *str)
{
        char c;

        while ((c = *str++))
                usart_putc(c);
}
