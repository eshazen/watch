
#include <stdio.h>
#include "display_list.h"

void draw_test( int x0, int y0, int color) {
  printf("plot (%d, %d) in color %d\n", x0, y0, color);
}

int main( int argc, char *argv[]) {
  dl_setup( draw_test, 0, 10, 0, 10);
  dl_draw_clipped_line( 0, 0, 10, 20, 5);
  dl_setup( draw_test, 0, 10, 10, 20);
  dl_draw_clipped_line( 0, 10, 10, 20, 5);
}
