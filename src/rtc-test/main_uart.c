/*
 * UART stdio example
 * note that there is no editing on input!
 */

#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "my_gets.h"
#include "watch.h"
#include "parse.h"

// create a file pointer for read/write to USART0
FILE usart0_str = FDEV_SETUP_STREAM(USART0SendByte, USART0ReceiveByte, _FDEV_SETUP_RW);

static char buff[40];
#define MAXARG 4
static char *argv[MAXARG];
static int iargv[MAXARG];

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
    my_gets( buff, sizeof(buff));
    int argc = parse( buff, argv, iargv, MAXARG);
  }
}


