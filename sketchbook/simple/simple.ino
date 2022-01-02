#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h> 

int main(void) 
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
}

