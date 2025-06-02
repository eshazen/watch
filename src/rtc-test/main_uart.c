/*
 * UART stdio example
 * note that there is no editing on input!
 */

#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "watch.h"

// create a file pointer for read/write to USART0
FILE usart0_str = FDEV_SETUP_STREAM(USART0SendByte, USART0ReceiveByte, _FDEV_SETUP_RW);

static char buff[40];

int main (void)
{
  unsigned char c = ' ';

  LED_DDR |= LED_MASK;
  SW1_PORT |= _BV(SW1_BIT);	/* pull-ups */
  SW2_PORT |= _BV(SW2_BIT) | _BV(SW3_BIT);

  USART0Init();
  stdout = &usart0_str;		/* connect UART to stdout */
  stdin = &usart0_str;		/* connect UART to stdin */

  puts("UART Test");

  while( 1) {

    if( USART0CharacterAvailable()) {
      char c = USART0ReceiveByte(NULL);
      USART0SendByte(c+1, NULL);
      LED_PORT |= _BV(LED1_BIT);
      _delay_ms(100);
      LED_PORT &= ~_BV(LED1_BIT);
      _delay_ms(100);
    }

//    puts("> ");
//    fgets( buff, sizeof( buff), stdin);
//    for( int i=0; i<strlen(buff); i++) {
//      printf("%d: ", i);
//      unsigned char c = buff[i];
//      if( c < 0x20 || c > 0x7f)
//	printf("0x%x\n", c);
//      else
//	printf("%c\n", c);
//    }
  }
}


