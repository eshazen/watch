//
// try to draw a clock face
//


#include <SPI.h>
#include "epd1in54_V2.h"
#include "epdpaint.h"
#include <stdio.h>

Epd epd;
unsigned char image[1024];	// big enough for 128x64
Paint paint(image, 0, 0);

#define COLORED     0
#define UNCOLORED   1

int hours = 1;
int minutes = 15;

void show_clock(int hours, int minutes);

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
  show_clock( hours, minutes);
  epd.SetFrameMemory(paint.GetImage(), 10, 10, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();
  ++minutes;
  if( minutes == 60)
    ++hours;
  delay(1);
}
