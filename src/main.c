#include <avr/io.h>
#include <util/delay.h>
#include <ctype.h>

#include "usart.h"
#include "sim.h"
#include "macros.h"

static void flash_led(int times)
{
        while (times--) {
		PORTB |= (1<<PB5);
		sim_out('1');
		_delay_ms(500);
		PORTB &= ~(1<<PB5);
		sim_out('0');
		_delay_ms(500);
        }
}

static void usart_echo()
{
        usart_init(BAUD_ASYNC_NORMAL);

	for (;;) {
                char c = usart_getc();
                if (isdigit(c))
                        flash_led(digit_to_int(c));
                else if (islower(c))
                        usart_putc(toupper(c));
                else if (isupper(c))
                        usart_putc(c);
                else
                        usart_puts("\n\rerror\n\r");
	}
}

int main(void)
{
	DDRB |= (1 << PB5);
        flash_led(3);

        usart_echo();
}
