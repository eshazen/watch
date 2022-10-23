# EP-EPM0154-2R Software

## Installation

This display family is provided with some more-or-less working examples.  Installation steps:

Grab the zip from either the manufacturer page or local copy in `arduino` folder as 
`ER-EPM0154-2_Arduino_Tutorial.zip`.
This contains 3 sets of `Examples...` and `Libraries...` directories.

Copy the appropriate (in our case, the '..-2R') `Libraries` folder to the Arduino libraries
location, normally `~/Arduino/libraries/ER-EPM0154-2R`.

Then, make the following edits:

In `epdif.cpp` change "`#include <spi.h>`" to "`#include <SPI.h>`"

In `epdif.h` change "`#include <arduino.h>`" to "`#include <Arduino.h>`"

Now the example runs, at least in Arduino 1.8.19 under Ubuntu 22.04.

## Class Library

Here are the prototypes for `ER-EPM0154-2R.cpp`:

    Epd();
    ~Epd();
    int  Init(void);
    void SendCommand(unsigned char command);
    void SendData(unsigned char data);
    void WaitUntilIdle(void);
    void Reset(void);
     void SetFrameMemoryBlack(
        const unsigned char* image_buffer,
        int x,
        int y,
        int image_width,
        int image_height
    ); 
      void SetFrameMemoryRed(
        const unsigned char* image_buffer,
        int x,
        int y,
        int image_width,
        int image_height
    );   
    void SetFrameMemory(const unsigned char* frame_buffer_black, const unsigned char* frame_buffer_red);
    void ClearFrameMemory(void);
    void DisplayFrame(void);
    void Sleep(void);

### Use

Create one instance of `Epd` and use for all interactions with the display.

For drawing, the `paint` class manages a pixel buffer in RAM (keep in
mind RAM limitations!).  Each instance has a pointer to RAM area,
width, height and rotate flag (one of ROTATE_0, ROTATE_90, ROTATE_180,
ROTATE_270).  This is a 1-bit deep buffer, so you need two of them
for black and red.

There are a bunch of methods to draw pixels, characters, strings,
lines, rectangles, and circles to the buffer.

So, typically:

    unsigned char image[1200];
    Paint paint(image, 0, 0);
    Epd epd;

    if (epd.Init() != 0) fail();
    epd.ClearFrameMemory();
	
To write a string:

    paint.Clear(UNCOLORED);
    paint.DrawStringAt(0, 4, "Hello world!", &Font16, COLORED);
    epd.SetFrameMemoryBlack(paint.GetImage(), 0, 10, paint.GetWidth(), paint.GetHeight());
    epd.DisplayFrame();

### Methods

#### `Epd::Epd()`

Sets member variables for pin names (reset, dc, cs, bus) and width,
height from constants. Pins are defined in `epdif.h` while `width` and
`height` are define in `ER-EPM0154-2R.h`.

#### `Epd::Init()`

Initialize SPI via `EpdIf::IfINit()` (in `epdif.cpp`).  Sets pin modes
and initialize SPI.

#### `void Epd::SetFrameMemoryRed(`
#### `void Epd::SetFrameMemoryBlack(`

    const unsigned char* image_buffer,
    int x,
    int y,
    int image_width,
    int image_height)`
	
Copy image buffer to frame memory at specified coordinates.  Don't update display	


#### `void Epd::SetFrameMemory(const unsigned char* frame_buffer_black, const unsigned char* frame_buffer_red)`

Set frame memory from images in flash.

#### `Paint::Paint(unsigned char* image, int width, int height)`

Create a paint instance with pointer to RAM.  Width and height may be
set later (could be 0,0)

#### `Paint::Clear(int colored)`

Clear the image (slowly, with loop, calling `DrawAbsolutePixel`)

#### `void Paint::DrawAbsolutePixel(int x, int y, int colored)`

Set a pixel in the buffer (ignores rotation)

#### `void Paint::DrawPixel(int x, int y, int colored)`

Set a pixel in the buffer, taking into account rotation

#### `void Paint::DrawCharAt(int x, int y, char ascii_char, sFONT* font, int colored)`

Draw a character.  Font choices supplied (constants, stored in flash,
128 chars per font):

    Font8  (5 x 8)    1 byte/char  752 bytes
	Font12 (7 x 12)   1 byte/char  1128 bytes
	Font16 (11 x 16)  2 byte/char  3008 bytes
	Font20 (14 x 20)  2 byte/char  3760 bytes
	Font24 (17 x 24)  3 byte/char  6768 bytes
	
#### `Paint::DrawStringAt(int x, int y, const char* text, sFONT* font, int colored)`

Draw a string from RAM.  Note that there is (currently) no function to
write strings stored in flash.

There are various drawing functions:

#### `void Paint::DrawLine(int x0, int y0, int x1, int y1, int colored)`
#### `void Paint::DrawHorizontalLine(int x, int y, int line_width, int colored)`
#### `void Paint::DrawVerticalLine(int x, int y, int line_height, int colored)`
#### `void Paint::DrawRectangle(int x0, int y0, int x1, int y1, int colored)`
#### `void Paint::DrawFilledRectangle(int x0, int y0, int x1, int y1, int colored)`
#### `void Paint::DrawCircle(int x, int y, int radius, int colored)`
#### `void Paint::DrawFilledCircle(int x, int y, int radius, int colored)`
