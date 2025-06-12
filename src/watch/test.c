#include <stdio.h>

// try some array initializer fun

typedef struct {
  int x, y;
  int draw;
} a_point;

struct {
  a_point points[3];
} list =
  { 0,0,0, 1,1,1, 2,2,2};
