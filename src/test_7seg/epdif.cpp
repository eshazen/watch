/**
 *  @filename   :   epdif.cpp
 *  @brief      :   Implements EPD interface functions
 *                  Users have to implement all the functions in epdif.cpp
 *  @author     :   Yehui from Waveshare
 *
 *  Copyright (C) Waveshare     August 10 2017
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documnetation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to  whom the Software is
 * furished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <stdio.h>
#include <avr/pgmspace.h>

// #define DEBUG

#include "epdif.h"
#ifdef BAREMETAL
extern "C" {
#include "spi.h"
#include "ioport.h"
}
#else
#include <SPI.h>
#endif

EpdIf::EpdIf() {
};

EpdIf::~EpdIf() {
};

// 
void EpdIf::DigitalWrite(int pin, int value) {
#ifdef BAREMETAL
  if( value)
    set_io_bits( portz[pin].port, portz[pin].mask);
  else
    clear_io_bits( portz[pin].port, portz[pin].mask);
#else  
    digitalWrite(pin, value);
#endif
}

int EpdIf::DigitalRead(int pin) {
#ifdef BAREMETAL
  return (get_io_bits( portz[pin].pin, portz[pin].mask) != 0);
#else  
    return digitalRead(pin);
#endif
}

void EpdIf::DelayMs(unsigned int delaytime) {
#ifdef BAREMETAL
#ifdef DEBUG
  puts_P( PSTR("dly1"));
#endif  
  if( delaytime)
  for( int i=0; i<delaytime; i++)
    _delay_ms(1);
#else  
    delay(delaytime);
#endif
}

void EpdIf::SpiTransfer(unsigned char data) {
    DigitalWrite(CS_PIN, LOW);
#ifdef BAREMETAL
    spi_transmit(data);
#else    
    SPI.transfer(data);
#endif
    DigitalWrite(CS_PIN, HIGH);
}

int EpdIf::IfInit(void) {
#ifdef BAREMETAL
  set_io_bits( &RST_PIN_DDR, _BV(RST_PIN_BIT));
  set_io_bits( &DC_PIN_DDR, _BV(DC_PIN_BIT));
  set_io_bits( &CS_PIN_DDR, _BV(CS_PIN_BIT));
  set_io_bits( &BUSY_PIN_PORT, _BV(BUSY_PIN_BIT)); // enable pull-up
  // set SCK and MOSI low
  clear_io_bits( &SPI_PORT, _BV(SPI_MOSI_PIN));
  clear_io_bits( &SPI_PORT, _BV(SPI_SCK_PIN));
  // set CS high
  DigitalWrite( CS_PIN, HIGH);
  spi_init();
#else    
  pinMode(CS_PIN, OUTPUT);
  pinMode(RST_PIN, OUTPUT);
  pinMode(DC_PIN, OUTPUT);
  pinMode(BUSY_PIN, INPUT); 

  SPI.begin();
  SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
#endif
  return 0;
}
