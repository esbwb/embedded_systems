#include <avr/io.h>

#include "usart.h"
#include "macros.h"

void usart_init(const unsigned int ubrr)
{
        /* Write high byte of baud rate to ubrr */
        UBRR0H = (unsigned char)(ubrr>>8);
        /* Write low byte of baud rate to ubrr */
        UBRR0L = (unsigned char) ubrr;

        /* Enable receiver and transmitter */
        UCSR0B = (1<<RXEN0) | (1<<TXEN0);

        /* Set frame format to 8n1 */
        UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
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
