#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

//
// define various point storage options
//
#include <stdint.h>

typedef enum {
  P_MOVE,
  P_DRAW,
  P_END
} t_draw;

typedef struct {
  t_draw draw;
  double x, y;
} d_point;

typedef struct {
  t_draw draw;
  int x, y;
} i_point;

typedef struct {
  t_draw draw;
  uint8_t x, y;
} b_point;


#endif
