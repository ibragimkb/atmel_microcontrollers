#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

#include <SoftSerial.h>     /* Allows Pin Change Interrupt Vector Sharing */
#include <TinyPinChange.h>  /* Ne pas oublier d'inclure la librairie <TinyPinChange> qui est utilisee par la librairie <RcSeq> */
SoftSerial mySerial(2, 3); // RX, TX

volatile uint8_t i = 0;
volatile uint8_t led = 1;

static inline void initTimer1(void)
{
  TCCR1 |= (1 << CTC1);  // clear timer on compare match
  TCCR1 |= (1 << CS13) | (1 << CS12) | (1 << CS11); //clock prescaler 8192
  OCR1C = 64; //122; // compare match value 
  TIMSK |= (1 << OCIE1A); // enable compare match interrupt
}

ISR(TIMER1_COMPA_vect)
{
  if(i == 16) {
    i = 0;
    if (led == 1) {
      PORTB |= (1 << PB1);
      led = 0;
    }
    else {
      PORTB &= ~(1 << PB1);
      led =1;
    }
  }
  else 
    i++;
	
	//PORTB = i;  // write updated i to PORTB
}

int main(void)
{
  
  // inits
  DDRB |= (1 << PB1);   // set data direction register for PB3 as output  

	initTimer1();        // initialize timer registers
	sei();               // enable interrupts

  // set the data rate for the SoftwareSerial port
  mySerial.begin(4800);
  mySerial.println("Hello, world?");
	
	while(1)
	{
	}
	
	return 0;
}

/*int main(void) 
{
  // inits
  DDRB |= (1 << PB1);   // set data direction register for PB3 as output  
  
  // event loop
  while (1)
 {
    PORTB |= (1 << PB1);   // turn on led
    _delay_ms(2500);      // delay 250 ms

    PORTB &= ~(1 << PB1);  // turn off led
    _delay_ms(2500);      // delay 250 ms
  }                                                
  return (0);                           
}*/

