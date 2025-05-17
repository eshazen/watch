
#define CLOCK_FUN_EXT extern

#include "clock_fun.h"

#define INTEGER_POINTS

// draw a polygon at position pos (0-59)
void draw_poly( int pos, int len, a_point* p) {
  a_point rp;

  // convert position 0..59 to angle 0..2PI
  //  double ang = ( (double)(60-pos)/60.)*2.*PI+CRT_ROT;
  double ang = ( (double)(pos)/60.)*2.*PI+CRT_ROT;

  for( int i=0; i<len; i++) {
    rp = rotate( p[i], ang);
    print_point( rp);
  }
}  

// draw a tick
void draw_tick( int pos, double inner, double outer)
{
  a_point p[] = {
    { 0, 0, inner},
    { 1, 0, outer}};

  draw_poly( pos, sizeof(p)/sizeof(a_point), p);
}


// draw a hand at position pos (0-59) with width and length
void draw_hand( int pos, double wid, double len)
{
  // initialize a triangle for the hand
  a_point p[] = {
    { 0, -wid/2, 0},
    { 1, -wid/4, len/2},
    { 1, 0, len},
    { 1, wid/4, len/2},
    { 1, wid/2, 0},
    { 1, -wid/2, 0}};

  // zero-width option
  a_point p0[] = {
    { 0, 0, 0},
    { 1, 0, len/2},
    { 1, 0, len},
    { 0, 0, 0}};

  if( debug)
    printf("%s draw_hand( %d, %f, %f)\n", 
	   ps ? "%" : ";", pos, len, wid);

  if( wid > 0)
    draw_poly( pos, sizeof(p)/sizeof(a_point), p);
  else
    draw_poly( pos, sizeof(p)/sizeof(a_point), p0);

}


a_point rotate( a_point p, double a)
{
  a_point rp;

  rp.x = p.x*cos(a)-p.y*sin(a);
  rp.y = p.x*sin(a)+p.y*cos(a);
  rp.draw = p.draw;

  return rp;
}


void print_point( a_point p ) {
  p.x = p.x * scale + offset;
  p.y = p.y * scale + offset;
  // just print the point formatted for C
  // special case for end (omit comma)
#ifdef INTEGER_POINTS
  if( p.draw == -1) {
    printf("  %d, %d, %d\n", (int)p.x, (int)p.y, 255);
  } else {
    printf("  %d, %d, %d,\n", (int)p.x, (int)p.y, p.draw);
  }
#else
  if( p.draw == -1) {
    printf("  %f, %f, %d\n", p.x, p.y, 255);
  } else {
    printf("  %f, %f, %d,\n", p.x, p.y, p.draw);
  }
#endif

}
