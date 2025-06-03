/*
 * interative test for watch
 */

#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <ctype.h>
#include "uart.h"
#include "my_gets.h"
#include "watch.h"
#include "parse.h"
#include "i2c.h"

// create a file pointer for read/write to USART0
FILE usart0_str = FDEV_SETUP_STREAM(USART0SendByte, USART0ReceiveByte, _FDEV_SETUP_RW);

static char buff[40];
#define MAXARG 8
static char *argv[MAXARG];
static int iargv[MAXARG];

static uint8_t rc;

// arrays for I2C I/O
#define MAXI2C 8
static uint8_t i2c_adr;
static uint8_t i2c_wdata[MAXI2C];
static uint8_t i2c_rdata[MAXI2C];

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
    char cmd = toupper( *argv[0]);
    switch( cmd) {
    case 'H':
      puts("W <tadr> <radr> [data...]");
      puts("R <tadr> <radr> <count>");
      break;
    case 'W':			/* I2C write */
      // copy the register address
      i2c_adr = iargv[2];
      // copy the write data
      for( int i=2; i<argc; i++)
	i2c_wdata[i-1] = iargv[i];
      rc = i2c_io( iargv[1], &i2c_adr, 1, i2c_wdata, argc-2, NULL, 0);
      if( rc)
	puts("I2C err");
      break;
    case 'R':
      // copy the register address
      i2c_adr = iargv[2];
      rc = i2c_io( iargv[1], &i2c_adr, 1, NULL, 0, i2c_rdata, iargv[3]);
      if( rc)
	puts("I2C err");
      for( int i=0; i<iargv[3]; i++)
	snprintf( buff, sizeof(buff), "%d: %02x\n", i, i2c_rdata[i]);
      break;
    }
  }
}


