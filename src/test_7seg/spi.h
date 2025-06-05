#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

#include <stdint.h>

// SPI pins
#define SPI_PORT PORTB
#define SPI_DDR DDRB
#define SPI_MOSI_PIN PB3
#define SPI_MISO_PIN PB4
#define SPI_SCK_PIN PB5

void spi_init();
void spi_transmit( uint8_t d);
uint8_t spi_receive();

#endif
