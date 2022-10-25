#include <SPI.h>
#include "epd1in54_V2.h"
#include "imagedata.h"
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

void setup()
{
  // put your setup code here, to run once:
  epd.LDirInit();
  epd.Clear();

  paint.SetWidth(64);
  paint.SetHeight(128);

  paint.Clear(UNCOLORED);

}

void loop()
{
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
  delay(1000);

  tyme++;
}
