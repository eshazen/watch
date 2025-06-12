//
// clipped display list drawing functions (C version)
//
#include <stddef.h>
#include <stdint.h>

#include "clock_stuff/point.h"

// generic drawing function provided by user (x, y, color)
typedef void (*draw_func)(int, int, int);

void dl_setup( draw_func df, int dl_xmin, int dl_xmax, int dl_ymin, int dl_ymax);
void dl_draw_from_list( int color, b_point* list, int limit);
void dl_draw_clipped_line( int x0, int y0, int x1, int y1, int color);
int dl_get_width(void);
void dl_set_width(int);
int dl_get_height(void);
void dl_set_height(int);
