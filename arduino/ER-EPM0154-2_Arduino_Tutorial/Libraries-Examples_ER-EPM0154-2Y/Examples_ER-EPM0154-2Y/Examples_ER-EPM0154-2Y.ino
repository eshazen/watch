/*Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
Examples for ER-EPM0154-2Y 
Display is Hardward SPI 4-Wire SPI Interface 
Tested and worked with:
Works with Arduino 1.6.0 IDE  
Works with Arduino DUE,Arduino mega2560,Arduino UNO Board
****************************************************/

#include <SPI.h>
#include "ER-EPM0154-2Y.h"
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
  // put your setup code here, to run once:
  Serial.begin(9600);
  if (epd.Init() != 0) {
      Serial.print("e-Paper init failed");
      return;
  }

  epd.ClearFrameMemory();   // bit set = white, bit reset = black
  //paint.SetRotate(ROTATE_0);
  paint.SetWidth(180);    // width should be the multiple of 8 
  paint.SetHeight(20);

  //For simplicity, the arguments are explicit numerical coordinates 
  paint.Clear(COLORED);
  paint.DrawStringAt(0, 4, "Hello world!", &Font16, UNCOLORED);
  epd.SetFrameMemoryBlack(paint.GetImage(), 0, 10, paint.GetWidth(), paint.GetHeight());

  paint.Clear(COLORED);
  paint.DrawStringAt(0, 4, "buydisplay.com", &Font16, UNCOLORED);
  epd.SetFrameMemoryRed(paint.GetImage(), 0, 35, paint.GetWidth(), paint.GetHeight());

  paint.SetWidth(64);
  paint.SetHeight(64);
  
  paint.Clear(UNCOLORED);
  paint.DrawRectangle(0, 0, 40, 50, COLORED);
  paint.DrawLine(0, 0, 40, 50, COLORED);
  paint.DrawLine(40, 0, 0, 50, COLORED);
  epd.SetFrameMemoryBlack(paint.GetImage(), 0, 60, paint.GetWidth(), paint.GetHeight());

  paint.Clear(UNCOLORED);
  paint.DrawCircle(28, 28, 25, COLORED);
  epd.SetFrameMemoryBlack(paint.GetImage(), 50, 60, paint.GetWidth(), paint.GetHeight());

  paint.Clear(COLORED);
  paint.DrawFilledRectangle(0, 0, 40, 50, UNCOLORED);
  epd.SetFrameMemoryRed(paint.GetImage(), 0, 145, paint.GetWidth(), paint.GetHeight());

  paint.Clear(COLORED);
  paint.DrawFilledCircle(28, 28, 25,UNCOLORED);
  epd.SetFrameMemoryRed(paint.GetImage(), 50, 145, paint.GetWidth(), paint.GetHeight());
 
  epd.DisplayFrame();
  delay(2000);

  if (epd.Init() != 0) {
      Serial.print("e-Paper init failed");
      return;
  }


  epd.SetFrameMemory(IMAGE_BLACK, IMAGE_RED);
  epd.DisplayFrame();
   delay(2000);  

  
  epd.SetFrameMemory(IMAGE_BLACK1, IMAGE_RED1);
  epd.DisplayFrame(); 
 delay(2000);


 
 delay(15000);
  epd.ClearFrameMemory();
  epd.DisplayFrame(); 

  epd. Sleep();
}

void loop() {
  delay(500);
}

