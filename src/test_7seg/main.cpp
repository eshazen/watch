//
// test waveshare display on real hardware
//


#ifdef BAREMETAL
extern "C" {
#include "spi.h"
}
#else
#include <SPI.h>
#endif

#include <stdio.h>
#include <avr/pgmspace.h>

#include "epd1in54_V2.h"
#include "imagedata.h"
#include "epdpaint.h"
#include "watch.h"


extern "C" {
#include "uart.h"
#include "ioport.h"
}

#include <stdio.h>

extern FILE usart0_str;		  // file descriptor so we can use printf() etc
static char buff[40];

Epd epd;
unsigned char image[1024];
Paint paint(image, 0, 0);

unsigned long time_start_ms;
unsigned long time_now_s;
#define COLORED     0
#define UNCOLORED   1

unsigned char seglen = 35;
unsigned char segwid = 5;

unsigned char dighgt = seglen*2+segwid;
unsigned char digdx = seglen + 2* segwid;
unsigned char x = 5;

static int tyme = 0;
static uint8_t led_val = 0;

int main( int argc, char *argv[]) {

  // LED init
  LED_DDR |= LED_MASK;
  SW1_PORT |= _BV(SW1_BIT);	/* pull-ups */
  SW2_PORT |= _BV(SW2_BIT) | _BV(SW3_BIT);

  // nSS (PB2) must be output to avoid SPI problems
  DDRB |= _BV(2);

  set_io_bits( &LED_PORT, _BV(LED1_BIT));
  set_io_bits( &LED_PORT, _BV(LED2_BIT));

  USART0Init();
  spi_init();

  stdout = &usart0_str;		/* connect UART to stdout */
  stdin = &usart0_str;		/* connect UART to stdin */

  _delay_ms(5000);

  puts_P( PSTR("start"));

  // put your setup code here, to run once:
  epd.LDirInit();
  puts_P( PSTR("init"));
  epd.Clear();

  // 64 * 128 * 8 = 1024 (size of the image bitmap)
  paint.SetWidth(64);
  paint.SetHeight(128);

  paint.Clear(UNCOLORED);

  // turn off LED2
  clear_io_bits( &LED_PORT, _BV(LED2_BIT));

  puts_P( PSTR("run"));

  while( 1) 
    {
      led_val ^= 1;
      if( led_val)
	set_io_bits( &LED_PORT, _BV(LED1_BIT));
      else
	clear_io_bits( &LED_PORT, _BV(LED1_BIT));

      x = 5;
  
      paint.DrawSeg7DigitAt( 0, 0, seglen, segwid, (tyme/1000) % 10, COLORED); /* draw '0' at (0,0) */
      epd.SetFrameMemory(paint.GetImage(), x, 5, paint.GetWidth(), paint.GetHeight());
      x += digdx;

      paint.DrawSeg7DigitAt( 0, 0, seglen, segwid, (tyme/100) % 10, COLORED); /* draw '0' at (0,0) */
      epd.SetFrameMemory(paint.GetImage(), x, 5, paint.GetWidth(), paint.GetHeight());
      x += digdx+10;

      paint.DrawSeg7DigitAt( 0, 0, seglen, segwid, (tyme/10) % 10, COLORED); /* draw '0' at (0,0) */
      epd.SetFrameMemory(paint.GetImage(), x, 5, paint.GetWidth(), paint.GetHeight());
      x += digdx;

      paint.DrawSeg7DigitAt( 0, 0, seglen, segwid, tyme % 10, COLORED); /* draw '0' at (0,0) */
      epd.SetFrameMemory(paint.GetImage(), x, 5, paint.GetWidth(), paint.GetHeight());

      epd.DisplayFrame();
      _delay_ms( 1000);

      tyme++;
    }
}
