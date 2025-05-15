#include "test_paint.h"
#include <stdio.h>

void Paint::DrawPixel( int x, int y, int colored) {
  printf( "(%d, %d)\n", x, y);
}
