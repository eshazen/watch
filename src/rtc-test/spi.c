// spi.c - super simple SPI library for AVR

#include <avr/io.h>
#include "spi.h"

void spi_init() {
  SPI_DDR |= _BV(SPI_SCK_PIN) | _BV(SPI_MOSI_PIN);
  // enable SPI, set as master, rate = fosc/16 (62.5kHz for 1MHz clock)
  SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPR0);
}

void spi_transmit( uint8_t d) {
  SPDR = d;
  while( !(SPSR & _BV(SPIF)))
    ;
}

uint8_t spi_receive() {
  while( !(SPSR & _BV(SPIF)))
    ;
  return SPDR;
}
