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
  double x, y;
  t_draw draw;
} d_point;

typedef struct {
  int x, y;
  t_draw draw;
} i_point;

typedef struct {
  uint8_t x, y;
  t_draw draw;
} b_point;


#endif
