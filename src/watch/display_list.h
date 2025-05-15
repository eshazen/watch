//
// clipped display list drawing functions (C version)
//
typedef void (*draw_func)(int, int, int);

void dl_setup( draw_func df, int dl_xmin, int dl_xmax, int dl_ymin, int dl_ymax);
void dl_draw_from_list( int npoint, int* xpoints, int* ypoints, unsigned char* movedraw, int color);
void dl_draw_clipped_line( int x0, int y0, int x1, int y1, int color);
int dl_get_width(void);
void dl_set_width(int);
int dl_get_height(void);
void dl_set_height(int);
