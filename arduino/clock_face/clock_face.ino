//
// try to draw a clock face
//


#include <SPI.h>
#include "epd1in54_V2.h"
// #include "imagedata.h"
#include "epdpaint.h"
#include <stdio.h>

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

int tyme = 0;

int hours = 1;
int minutes = 15;

void show_clock(int hours, int minutes);

void setup()
{
  // put your setup code here, to run once:
  epd.LDirInit();
  epd.Clear();

  paint.SetWidth(64);
  paint.SetHeight(64);

  paint.Clear(UNCOLORED);

}

void loop()
{
  show_clock( hours, minutes);
  epd.SetFrameMemory(paint.GetImage(), 10, 10, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();
  ++minutes;
  if( minutes == 60)
    ++hours;
  delay(1);
}
