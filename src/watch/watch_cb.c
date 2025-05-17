#include "watch.h"
#include "clock_stuff/clock.h"

#include <time.h>

/* Callbacks and freeobj handles for form watch_top */

/***************************************
 ***************************************/

static int win_x0, win_y0, win_wid, win_hgt;


// provide a drawing function
// which "knows" the coordinates and size of the region to draw in
void draw_point( int x, int y, long color) {
  // clip to region
  if( x > 0 && x < win_wid && y > 0 && y < win_wid) {
    fl_point( x + win_x0, y + win_y0, color);
  }
}

extern FD_watch_top *fd;

unsigned char* draw_list( unsigned char *p) {
  unsigned int x0, y0, x1, y1;
  printf("Draw list first point (%d, %d) %d\n", p[0], p[1], p[2]);
  while( p[2] != 255) {
    if( p[2] == 0) {
      x0 = p[0];
      y0 = p[1];
      // printf("Move: (%d, %d)\n", x0, y0);
    } else {
      x1 = p[0];
      y1 = p[1];
      //      printf("Draw: (%d, %d)\n", x1, y1);
      printf("line (%d, %d) - (%d, %d)\n", x0, y0, x1, y1);
      fl_line( win_x0+x0, win_y0+y0, win_x0+x1, win_y0+y1, FL_RED);
      x0 = x1;
      y0 = y1;
    }
    p += 3;
  }
  return p+3;
}

unsigned char* index_list( unsigned char *p, int n) {
  unsigned char* rp;
  int dn = n;
  rp = p;
  if( dn) {
    while( dn--) {
      while( rp[2] != 255) {
	rp += 3;
      }
      rp += 3;
    }
  }
  printf("index_list( %d) offset: %ld\n", n, rp-p);
  return rp;
}

void cb_clock( FL_OBJECT * ob,
         long        data )
{
  // get the time
  time_t now = time(NULL);
  struct tm *local_time = localtime(&now);
  int hours = local_time->tm_hour;
  int minutes = local_time->tm_min;

  // get coordinates of screen
  fl_get_object_geometry( fd->screen, &win_x0, &win_y0,
			  &win_wid, &win_hgt);

  minutes = fl_get_slider_value( fd->s_min);
  hours = fl_get_slider_value( fd->s_hour);
  

  fl_rectf( win_x0, win_y0, win_wid, win_hgt, FL_WHITE);

  draw_list( clock_tics);
  draw_list( index_list( clock_minutes, minutes));
  // adjust hours from 0..12 to 0..60
  hours = (hours%12)*5 + (float)(minutes/60.)*5;
  draw_list( index_list( clock_hours, hours));

}




/***************************************
 ***************************************/

void
cb_hour( FL_OBJECT * obj,
         long        data )
{
    /* Fill-in code for callback here */
}


/***************************************
 ***************************************/

void
cb_min( FL_OBJECT * obj,
        long        data )
{
    /* Fill-in code for callback here */
}



