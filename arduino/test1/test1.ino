
//
// initial test to see if we understand the library
//

#include <SPI.h>
#include "ER-EPM0154-2R.h"
#include "epdpaint.h"
#include "imagedata.h"

#define COLORED     0
#define UNCOLORED   1

/**
  * Due to RAM not enough in Arduino UNO, a frame buffer is not allowed.
  * In this case, a smaller image buffer is allocated and you have to 
  * update a partial display several times.
  * 1 byte = 8 pixels, therefore you have to set 8*N pixels at a time.
  */
unsigned char image[1200];
Paint paint(image, 0, 0);
Epd epd;

void setup() {
  uint8_t cur_line = 0;

  Serial.begin(9600);
  if (epd.Init() != 0) {
      Serial.println("e-Paper init failed");
      return;
  }

  Serial.println("\n\npass 1: clear mem()");
  epd.ClearFrameMemory();   // bit set = white, bit reset = black

  Serial.println("draw()");
  paint.SetWidth(128);    // width should be the multiple of 8 
  paint.SetHeight(24);

  //For simplicity, the arguments are explicit numerical coordinates 
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 0, "Font24", &Font24, COLORED);
  epd.SetFrameMemoryBlack(paint.GetImage(), 0, cur_line, paint.GetWidth(), paint.GetHeight());
  cur_line += Font24.Height;

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 0, "Font20", &Font20, COLORED);
  epd.SetFrameMemoryBlack(paint.GetImage(), 0, cur_line, paint.GetWidth(), paint.GetHeight());
  cur_line += Font20.Height;

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 0, "Font16", &Font16, COLORED);
  epd.SetFrameMemoryBlack(paint.GetImage(), 0, cur_line, paint.GetWidth(), paint.GetHeight());
  cur_line += Font16.Height;

  Serial.println("display()");
  epd.DisplayFrame();
  Serial.println("done()");
  delay(5000);


  Serial.println("\n\npass 2: nclear mem()");
  epd.ClearFrameMemory();   // bit set = white, bit reset = black

  Serial.println("draw()");
  paint.SetWidth(128);    // width should be the multiple of 8 
  paint.SetHeight(24);

  //For simplicity, the arguments are explicit numerical coordinates 
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 0, "Font24", &Font24, COLORED);
  epd.SetFrameMemoryBlack(paint.GetImage(), 0, cur_line, paint.GetWidth(), paint.GetHeight());
  cur_line += Font24.Height;

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 0, "Font20", &Font20, COLORED);
  epd.SetFrameMemoryBlack(paint.GetImage(), 0, cur_line, paint.GetWidth(), paint.GetHeight());
  cur_line += Font20.Height;

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 0, "Font16", &Font16, COLORED);
  epd.SetFrameMemoryBlack(paint.GetImage(), 0, cur_line, paint.GetWidth(), paint.GetHeight());
  cur_line += Font16.Height;

  Serial.println("display()");
  epd.DisplayFrame();
  Serial.println("done()");
  delay(5000);

  



  Serial.println("sleep()");
  epd.Sleep();

  while(1)
    ;

}


void loop() {
  delay(500);
}
