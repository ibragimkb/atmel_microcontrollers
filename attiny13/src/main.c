#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//#define LED_PIN PB0
#define LED_BIT _BV(PB4)
#define LED_BIT0 _BV(PB0)
#define LED_BIT1 _BV(PB1)
#define LED_BIT2 _BV(PB2)

static unsigned char c;
static unsigned char b;
volatile unsigned char h = 0;
volatile unsigned char n = 16;
volatile char d = 1;

void direct()
{
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
        b = 1;
        PORTB ^= LED_BIT2;
        PORTB ^= LED_BIT1;
    }    
}

void reverse()
{
    if (b == 0) {
        PORTB ^= LED_BIT1; // toggle LED pin
        b++;
    }
    else if (b == 1){
        PORTB ^= LED_BIT1; // toggle LED pin
        PORTB ^= LED_BIT0;
        b++;
    }
    else if (b == 2)
    {
        PORTB ^= LED_BIT0; // toggle LED pin
        PORTB ^= LED_BIT2;
        b++;
    }
    else {
        b = 1;
        PORTB ^= LED_BIT1;
        PORTB ^= LED_BIT2;
    }    
}

void reset_ports()
{
    PORTB = 0b00000000;
    b = 0;
}

ISR(TIM0_COMPA_vect)
{

    if (h == 64) {
        PORTB ^= LED_BIT;
        h = 0;
        ADCSRA |= _BV(ADSC);
    } // toggle LED pin
	if (c == n) {
	        //PORTB ^= _BV(LED_PIN); // toggle LED pin
		//PORTB ^= LED_BIT; // toggle LED pin
        if (d == 0) direct();
        else reverse();

		c = 0;
	}
	c++;
    h++;
    if (c > n) c = 0;

}

ISR(ADC_vect)
{
    //n = ADCH >> 2;
    n = ADCH;
    if (n > 127) {
        n = (256 - n) >> 2;
        //n = ADCH >> 3;
        if (d != 0) { reset_ports(); }
        d = 0;
    }
    else {
        n = ADCH >> 2;
        if (d != 1) reset_ports();
        d = 1;
    }

    if (n < 2) n = 2;
    //else if (n > 128) n = 128;
    //ADCSRA |= _BV(ADSC);
}

int main(void)
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
    
	//ADCSRA |= _BV(ADPS2)|_BV(ADPS0); // set ADC division factor to 256
	ADCSRA |= _BV(ADEN)|_BV(ADIE); // enable ADC interrupt
	//ADMUX = _BV(MUX1); // set ADC4 (PB4) as audio input
    ADMUX |= _BV(MUX0)|_BV(MUX1); // select ADC3 (PB3)
	ADMUX |= _BV(ADLAR); // left adjust of ADC result
	//ADCSRA |= _BV(ADATE); // set ADC auto-trigger
	ADCSRA |= _BV(ADSC); // start conversion
    
        sei(); // enable global interrupts

        //ADCSRA |= _BV(ADSC); // start first signal acquisition
        /* loop */
        while (1);
}
