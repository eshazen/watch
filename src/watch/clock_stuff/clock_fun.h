#ifndef CLOCK_FUN_EXT
#define CLOCK_FUN_EXT
#endif

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

#include "point.h"

#define PI (3.14159265)

// angle in radians to correct for CRT rotation
// #define CRT_ROT (PI-0.489)
// #define CRT_ROT (PI-0.489+.05)
// Could also use to rotate display for other purposes
#define CRT_ROT (PI)

d_point rotate( d_point p, double theta);
void draw_hand( int pos, double wid, double len);
void print_point( d_point);
void draw_tick( int pos, double inner, double outer);

CLOCK_FUN_EXT int avr_progmem;	/* flag: AVR flash memory output */
CLOCK_FUN_EXT int ps;		/* flag: postscript output */
CLOCK_FUN_EXT double offset;
CLOCK_FUN_EXT double scale;
CLOCK_FUN_EXT int debug;

// output for Z80 display list
#define MAXPT 1000
CLOCK_FUN_EXT uint16_t zx[MAXPT], zy[MAXPT];
CLOCK_FUN_EXT int npt;		/* number of points in group */


