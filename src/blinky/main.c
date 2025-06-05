/*
 * blinky example for watch
 */

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#include "watch.h"

int main (void)
{

  LED_DDR |= LED_MASK;
  SW1_PORT |= _BV(SW1_BIT);	/* pull-ups */
  SW2_PORT |= _BV(SW2_BIT) | _BV(SW3_BIT);

  while( 1) {

//    if( SW1_PRESSED)
//      LED_PORT |= _BV(LED1_BIT);
//    else
//      LED_PORT &= ~_BV(LED1_BIT);
//
//    if( SW3_PRESSED)
//      LED_PORT |= _BV(LED2_BIT);
//    else
//      LED_PORT &= ~_BV(LED2_BIT);
      
	

    LED_PORT |= (1 << LED1_BIT);
    _delay_ms( 500);
    LED_PORT &= ~(1 << LED1_BIT);
    _delay_ms( 500);
    LED_PORT |= (1 << LED2_BIT);
    _delay_ms( 500);
    LED_PORT &= ~(1 << LED2_BIT);
    _delay_ms( 500);
  }
}


