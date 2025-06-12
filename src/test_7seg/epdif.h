/**
 *  @filename   :   epdif.h
 *  @brief      :   Header file of epdif.cpp providing EPD interface functions
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

#ifndef EPDIF_H
#define EPDIF_H

#ifdef BAREMETAL
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#else
#include <Aruino.h>
#endif

#ifdef BAREMETAL

// define a few things to provide similarity to Arduino world
#define HIGH 1
#define LOW 0

// RST_PIN  PB0
// DC_PIN   PB1
// CS_PIN   PD6
// BUSY_PIN PD7

#define RST_PIN_PORT PORTB
#define RST_PIN_BIT 0
#define RST_PIN_DDR DDRB

#define DC_PIN_PORT PORTB
#define DC_PIN_BIT 1
#define DC_PIN_DDR DDRB

#define CS_PIN_PORT PORTD
#define CS_PIN_BIT 6
#define CS_PIN_DDR DDRD

#define BUSY_PIN_PORT PORTD
#define BUSY_PIN_BIT 7
#define BUSY_PIN_DDR DDRD
#define BUSY_PIN_PIN PIND

// bogus pin numbers used as index into the portz[] struct array below
#define RST_PIN         0
#define DC_PIN          1
#define CS_PIN          2
#define BUSY_PIN        3

// define a struct so we can read/write by pin number
typedef struct {
  volatile uint8_t* port;
  volatile uint8_t* pin;
  uint8_t mask;
} a_port;

static a_port portz[] = {
  &RST_PIN_PORT, NULL, _BV(RST_PIN_BIT),
  &DC_PIN_PORT, NULL, _BV(DC_PIN_BIT),
  &CS_PIN_PORT, NULL, _BV(CS_PIN_BIT),
  &BUSY_PIN_PORT, &BUSY_PIN_PIN, _BV(BUSY_PIN_BIT)
};

#else

//---------- Arduino version ----------

// Pin definition
#define RST_PIN         8
#define DC_PIN          9
#define CS_PIN          10
#define BUSY_PIN        7
#endif

class EpdIf {
public:
    EpdIf(void);
    ~EpdIf(void);

    static int  IfInit(void);
    static void DigitalWrite(int pin, int value); 
    static int  DigitalRead(int pin);
    static void DelayMs(unsigned int delaytime);
    static void SpiTransfer(unsigned char data);
};

#endif
