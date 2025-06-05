/*
 * interative test for watch
 */

// #define DEBUG

#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <ctype.h>
#include <avr/pgmspace.h>

#include "uart.h"
#include "my_gets.h"
#include "watch.h"
#include "parse.h"
#include "i2c.h"

#include "spi.h"

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

void chk_err( uint8_t rc) {
  if( rc) {
    snprintf( buff, sizeof(buff), "I2C_err: 0x%02x", rc);
    puts(buff);
  }
}


int main (void)
{
  unsigned char c = ' ';

  LED_DDR |= LED_MASK;
  SW1_PORT |= _BV(SW1_BIT);	/* pull-ups */
  SW2_PORT |= _BV(SW2_BIT) | _BV(SW3_BIT);

  // nSS (PB2) must be output to avoid SPI problems
  DDRB |= _BV(2);

  USART0Init();
  stdout = &usart0_str;		/* connect UART to stdout */
  stdin = &usart0_str;		/* connect UART to stdin */

  spi_init();

  puts("UART Test");

  while( 1) {
    putchar('>');
    my_gets( buff, sizeof(buff));
    int argc = parse( buff, argv, iargv, MAXARG);
    char cmd = toupper( *argv[0]);
    char cmd2 = toupper( argv[0][1]);
    switch( cmd) {
    case 'H':
      puts_P( PSTR("W <tadr> <radr> [data...]"));
      puts_P( PSTR("R <tadr> <radr> <count>"));
      puts_P( PSTR("S <data>"));
      puts_P( PSTR("RR ... repeat"));
      break;
    case 'S':			/* SPI write */
      spi_transmit( iargv[1]);
      break;
    case 'W':			/* I2C write */
      // iargv[1] = I2C target address
      // iargv[2] = chip register address
      // iargv[3..n] = data
      // copy the register address
      i2c_adr = iargv[2];
      // copy the write data
      for( int i=2; i<argc; i++)
	i2c_wdata[i-1] = iargv[i];
      rc = i2c_io( iargv[1], &i2c_adr, 1, i2c_wdata, argc-2, NULL, 0);
      chk_err(rc);
      break;
    case 'R':
      // iargv[1] = I2c target address
      // iargv[2] = chip register address
      // iargv[3] = byte count
      // copy the register address
      i2c_adr = iargv[2];
#ifdef DEBUG
      snprintf( buff, sizeof(buff), "ad: %02x ra: %02x count: %d",
		iargv[1], i2c_adr, iargv[3]);
      puts( buff);
#endif      
      rc = i2c_io( iargv[1], &i2c_adr, 1, NULL, 0, i2c_rdata, iargv[3]);
      chk_err(rc);
      for( int i=0; i<iargv[3]; i++) {
	snprintf( buff, sizeof(buff), "%d: 0x%02x (%d)", i, i2c_rdata[i], i2c_rdata[i]);
	puts( buff);
      }
      if( cmd2 == 'R') {	/* repeat until key pressed */
	while( !USART0CharacterAvailable()) {
	  rc = i2c_io( iargv[1], &i2c_adr, 1, NULL, 0, i2c_rdata, iargv[3]);
	}
      }
      break;
    }
  }
}


