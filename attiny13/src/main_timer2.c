#include <avr/io.h>
#include <avr/interrupt.h>

//#define LED_PIN PB0
#define LED_BIT _BV(PB4)
#define LED_BIT0 _BV(PB0)
#define LED_BIT1 _BV(PB1)
#define LED_BIT2 _BV(PB2)

static int c;
static int b;

ISR(TIM0_COMPA_vect)
{
/*
	if (c == 16) {
	        //PORTB ^= _BV(LED_PIN); // toggle LED pin
		PORTB ^= LED_BIT; // toggle LED pin
		if (b == 0) {
			PORTB ^= LED_BIT0; // toggle LED pin
			b++;
		}
		else if (b == 1){
			PORTB ^= LED_BIT1; // toggle LED pin
			b++;
		}
		else if (b == 2)
		{
			PORTB ^= LED_BIT2; // toggle LED pin
			b++;
		}
		else {
			b = 0;
			PORTB = 0b00000000;
		}



		c = 0;
	}
	c++;
*/

	if (c == 16) {
	        //PORTB ^= _BV(LED_PIN); // toggle LED pin
		PORTB ^= LED_BIT; // toggle LED pin
		if (b == 0) {
			PORTB ^= LED_BIT2; // toggle LED pin
			b++;
		}
		else if (b == 1){
			PORTB ^= LED_BIT2; // toggle LED pin
			PORTB ^= LED_BIT0;
			b++;
		}
		else if (b == 2)
		{
			PORTB ^= LED_BIT0; // toggle LED pin
			PORTB ^= LED_BIT1;
			b++;
		}
		else {
			b = 0;
			PORTB ^= LED_BIT1;
		}



		c = 0;
	}
	c++;

}

int
main(void)
{

	c = 0;
	b = 0;
        /* setup */
        //DDRB = 0b00000001; // set LED pin as OUTPUT
	DDRB |= LED_BIT; // OUTPUT
	DDRB |= LED_BIT0; // OUTPUT
	DDRB |= LED_BIT1; // OUTPUT
	DDRB |= LED_BIT2; // OUTPUT
        PORTB = 0b00000000; // set all pins to LOW
        TCCR0A |= _BV(WGM01); // set timer counter mode to CTC
        //TCCR0B |= _BV(CS02)|_BV(CS00); // set prescaler to 1024 (CLK=1200000Hz/1024/256=4.57Hz, 0.22s)
	TCCR0B |= _BV(CS01)|_BV(CS00); // set prescaler to 1024 (CLK=1200000Hz/64/256=4.57Hz, 0.22s)
        OCR0A = 255; // set Timer's counter max value
	//OCR0A = 64; // set Timer's counter max value
        TIMSK0 |= _BV(OCIE0A); // enable Timer CTC interrupt
        sei(); // enable global interrupts

        /* loop */
        while (1);
}
