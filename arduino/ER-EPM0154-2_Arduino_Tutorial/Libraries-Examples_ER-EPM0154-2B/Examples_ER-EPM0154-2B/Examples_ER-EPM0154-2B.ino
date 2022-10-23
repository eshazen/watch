/*Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
Examples for ER-EPM0154-2B
Display is Hardward SPI 4-Wire SPI Interface 
Tested and worked with:
Works with Arduino 1.6.0 IDE  
Works with Arduino DUE,Arduino mega2560,Arduino UNO Board
****************************************************/

#include <SPI.h>
#include "ER-EPM0154-2B.h"
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
unsigned char image[1000];
Paint paint(image, 0, 0);
Epd epd;
unsigned long time_start_ms;
unsigned long time_now_s;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if (epd.Init() != 0) {
      Serial.print("e-Paper init failed");
      return;
  }

  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black

 
  //paint.SetRotate(ROTATE_0);
  paint.SetWidth(128);    // width should be the multiple of 8 
  paint.SetHeight(24);

  /* For simplicity, the arguments are explicit numerical coordinates */
  paint.Clear(COLORED);
  paint.DrawStringAt(0, 4, "Hello world!", &Font12, UNCOLORED);
  epd.SetFrameMemory(paint.GetImage(), 0, 10, paint.GetWidth(), paint.GetHeight());

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, "buydisplay.com", &Font12, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 0, 30, paint.GetWidth(), paint.GetHeight());

  paint.SetWidth(64);
  paint.SetHeight(64);
  
  paint.Clear(UNCOLORED);
  paint.DrawRectangle(0, 0, 40, 50, COLORED);
  paint.DrawLine(0, 0, 40, 50, COLORED);
  paint.DrawLine(40, 0, 0, 50, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 0, 60, paint.GetWidth(), paint.GetHeight());

  paint.Clear(UNCOLORED);
  paint.DrawCircle(28, 28, 24, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 48, 60, paint.GetWidth(), paint.GetHeight());

  paint.Clear(UNCOLORED);
  paint.DrawFilledRectangle(0, 0, 40, 50, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 0, 130, paint.GetWidth(), paint.GetHeight());

  paint.Clear(UNCOLORED);
  paint.DrawFilledCircle(28, 28, 24, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 48, 130, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();

  delay(2000);

  if (epd.Init() != 0) {
      Serial.print("e-Paper init failed");
      return;
  }


  epd.SetFrameMemory(IMAGE_DATA);
  epd.DisplayFrame();
 delay(2000);   

  epd.SendCommand(DISPLAY_UPDATE_CONTROL_1);
  epd.SendData(0x08);//Inverse RAM
   epd.DisplayFrame(); 
 delay(2000); 
 
   epd.SendCommand(DISPLAY_UPDATE_CONTROL_1);
  epd.SendData(0x00);//Normal
  epd.SetFrameMemory(IMAGE_DATA1);
  epd.DisplayFrame();
 delay(2000);   
 
   epd.SendCommand(DISPLAY_UPDATE_CONTROL_1);
  epd.SendData(0x08);//Inverse RAM
   epd.DisplayFrame(); 
 delay(2000);  


 delay(15000);
    epd.SendCommand(DISPLAY_UPDATE_CONTROL_1);
  epd.SendData(0x00);//Normal
  epd.ClearFrameMemory(0xFF);
  epd.DisplayFrame(); 


  epd. Sleep();
}

void loop() {
  delay(500);
}

