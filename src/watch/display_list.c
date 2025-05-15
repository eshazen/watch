//
// Process a display list to draw vectors in a virtual
// bitmap, divided into smaller physical bitmaps.
// As each physical bitmap is completed, send to device
//
#include <stdio.h>
#include "display_list.h"
// #include "epdpaint.h"
// #include "test_paint.h"

// #define DEBUG

static int dl_xmin, dl_xmax, dl_ymin, dl_ymax;
static draw_func dl_draw;

void dl_setup( draw_func df, int xmin, int xmax, int ymin, int ymax) {
#ifdef DEBUG
  printf("dl_setup( %d, %d, %d, %d)\n", xmin, xmax, ymin, ymax);
#endif
  dl_draw = df;
  dl_xmin = xmin;
  dl_xmax = xmax;
  dl_ymin = ymin;
  dl_ymax = ymax;
}

//
// traverse list of npoint points with coords in (xlist, ylist) and draw/move flag in draw
// clip against region size (width, height) with offset at xoff, yoff
// call paint->DrawPixel() for any pixels which fall in clip region
//
void dl_draw_from_list( int npoint, int* xlist, int* ylist, unsigned char* draw, int color) {
  if( npoint < 2)
    return;
  int x0 = xlist[0];
  int y0 = ylist[0];
  int x1, y1;
  for( int i=1; i<npoint; i++) {
    x1 = xlist[i];
    y1 = ylist[i];
    if( draw[i]) { 		// draw a line
      dl_draw_clipped_line( x0, y0, x1, y1, color);
    }
    x0 = x1;
    y0 = y1;
  }
}

void dl_draw_clipped_line( int x0, int y0, int x1, int y1, int color) {
  /* Bresenham algorithm */
  int dx = x1 - x0 >= 0 ? x1 - x0 : x0 - x1;
  int sx = x0 < x1 ? 1 : -1;
  int dy = y1 - y0 <= 0 ? y1 - y0 : y0 - y1;
  int sy = y0 < y1 ? 1 : -1;
  int err = dx + dy;

  while((x0 != x1) && (y0 != y1)) {
#ifdef DEBUG
    printf("pixel: (%d, %d)... ", x0, y0);
#endif    
    if ( x0 >= dl_xmin && x0 < dl_xmax && y0 >= dl_ymin && y0 < dl_ymax) {
#ifdef DEBUG
      printf("draw\n");
#endif      
      dl_draw( x0, y0, color);
    } else {
#ifdef DEBUG
      printf("\n");
#endif
      ;
    }
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
