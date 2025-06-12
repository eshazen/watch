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
void dump_point( b_point* p) {
  printf("(%d, %d) %d\n", p->x, p->y, p->draw);
}
#endif

//
// draw from a list of points until "draw" matches stop
// clip against region size (width, height) with offset at xoff, yoff
// 
//
void dl_draw_from_list( int color, b_point* list) {
  if( list[0].draw <= P_MOVE)	/* list must start with MOVE */
    return;
  int x1, y1;
  int x0 = list[0].x;
  int y0 = list[0].y;
#ifdef DEBUG
  printf("dl_draw_from_list( first= ");
  dump_point(&list[0]);
#endif  
  for( int i=1; list[i].draw != P_END; i++) {
#ifdef DEBUG
    printf("point %d ", i);
    dump_point( &list[i]);
#endif    
    x1 = list[i].x;
    y1 = list[i].y;
    if( list[i].draw) { 		// draw a line
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
