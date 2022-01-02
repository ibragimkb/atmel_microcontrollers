#include <avr/io.h>
#include <avr/interrupt.h>

//#define LED_PIN PB0
#define LED_BIT _BV(PB4)

static int c;

ISR(TIM0_COMPA_vect)
{

	if (c == 3) {
	        //PORTB ^= _BV(LED_PIN); // toggle LED pin
		PORTB ^= LED_BIT; // toggle LED pin
		c = 0;
	}
	c++;
}

int
main(void)
{

	c = 0;
        /* setup */
        //DDRB = 0b00000001; // set LED pin as OUTPUT
	DDRB |= LED_BIT; // OUTPUT
        PORTB = 0b00000000; // set all pins to LOW
        TCCR0A |= _BV(WGM01); // set timer counter mode to CTC
        TCCR0B |= _BV(CS02)|_BV(CS00); // set prescaler to 1024 (CLK=1200000Hz/1024/256=4.57Hz, 0.22s)
        OCR0A = 255; // set Timer's counter max value
        TIMSK0 |= _BV(OCIE0A); // enable Timer CTC interrupt
        sei(); // enable global interrupts

        /* loop */
        while (1);
}
