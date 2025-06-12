//
// Process a display list to draw vectors in a virtual
// bitmap, divided into smaller physical bitmaps.
// As each physical bitmap is completed, send to device
//
#include <stdio.h>
#include "display_list.h"

#define DEBUG

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

#ifdef DEBUG
void dump_point( b_point p) {
  printf("(%d, %d) %d\n", p.x, p.y, p.draw);
}
#endif

//
// draw from a list of points until "draw" matches stop
// clip against region size (width, height) with offset at xoff, yoff
// 
//
void dl_draw_from_list( int color, b_point* list, int limit) {
#ifdef DEBUG
  printf("dl_draw_from_list( first= ");
  dump_point(list[0]);
#endif  
  if( list[0].draw != P_MOVE)	/* list must start with MOVE */
    return;
  int x1, y1;
  int x0 = list[0].x;
  int y0 = list[0].y;
  for( int i=1; list[i].draw != P_END && i<limit; i++) {
#ifdef DEBUG
    printf("dl_draw_from_list point %d :", i);
    dump_point( list[i]);
#endif    
    x1 = list[i].x;
    y1 = list[i].y;
    if( list[i].draw) { 		// draw a line
#ifdef DEBUG
      printf("call dl_draw_clipped_line( %d, %d, %d, %d, %d)\n",
	     x0, y0, x1, y1, color);
#endif      
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

#ifdef DEBUG
  printf("enter dl_draw_clipped_line( %d, %d, %d, %d, %d)\n",
	 x0, y0, x1, y1, color);
#endif      

#ifdef DEBUG
  printf("enter loop x0=%d x1=%d y0=%d y1=%d\n",
	 x0, x1, y0, y1);
#endif    

  while((x0 != x1) && (y0 != y1)) {
#ifdef DEBUG
    printf("in loop x0=%d x1=%d y0=%d y1=%d\n",
	 x0, x1, y0, y1);
#endif    
    if ( x0 >= dl_xmin && x0 < dl_xmax && y0 >= dl_ymin && y0 < dl_ymax) {
#ifdef DEBUG
      printf("draw\n");
#endif      
      dl_draw( x0, y0, color);
    } else {
#ifdef DEBUG
      printf("clip\n");
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
#ifdef DEBUG
  printf("draw_clipped_line exit x0=%d x1=%d y0=%d y1=%d\n",
	 x0, x1, y0, y1);
#endif  
}
