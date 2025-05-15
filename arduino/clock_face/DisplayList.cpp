//
// Process a display list to draw vectors in a virtual
// bitmap, divided into smaller physical bitmaps.
// As each physical bitmap is completed, send to device
//
#include "DisplayList.hh"
#include "epdpaint.h"

DisplayList::DisplayList( Paint* pp, int width, int height) {
  this->paint = pp;
  this->width = width % 8 ? width + 8 - (width % 8) : width;
  this->height = height;
}

int DisplayList::GetWidth(void) {
    return this->width;
}

void DisplayList::SetWidth(int width) {
    this->width = width % 8 ? width + 8 - (width % 8) : width;
}

int DisplayList::GetHeight(void) {
    return this->height;
}

void DisplayList::SetHeight(int height) {
    this->height = height;
}

//
// traverse list of npoint points with coords in (xlist, ylist) and draw/move flag in draw
// clip against region size (width, height) with offset at xoff, yoff
// call paint->DrawPixel() for any pixels which fall in clip region
//
void DisplayList::DrawFromList( int npoint, int* xlist, int* ylist, byte* draw, int xoff, int yoff, int colored) {
  if( npoint < 2)
    return;
  int x0 = xlist[0];
  int y0 = ylist[0];
  int x1, y1;
  for( int i=1; i<npoint; i++) {
    x1 = xlist[i];
    y1 = ylist[i];
    if( draw[i]) { 		// draw a line
      DrawClipped( x0, y0, x1, y1, xoff, xoff+width, yoff, yoff+width, colored);
    }
    x0 = x1;
    y0 = y1;
  }
}

void DisplayList::DrawClipped( int x0, int y0, int x1, int y1, int xmin, int xmax, int ymin, int ymax, int colored) {
  /* Bresenham algorithm */
  int dx = x1 - x0 >= 0 ? x1 - x0 : x0 - x1;
  int sx = x0 < x1 ? 1 : -1;
  int dy = y1 - y0 <= 0 ? y1 - y0 : y0 - y1;
  int sy = y0 < y1 ? 1 : -1;
  int err = dx + dy;

  while((x0 != x1) && (y0 != y1)) {
    if ( x0 >= xmin && x0 < xmax && y0 >= ymin && y0 < ymax)
      paint->DrawPixel(x0, y0 , colored);
    if (2 * err >= dy) {     
      err += dy;
      x0 += sx;
    }
    if (2 * err <= dx) {
      err += dx; 
      y0 += sy;
    }
  }
}
