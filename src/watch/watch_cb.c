#include "watch.h"
#include "display_list.h"
#include "clock_stuff/point.h"
#include "clock_stuff/clock_hands.h"

#include <time.h>

/* Callbacks and freeobj handles for form watch_top */

/***************************************
 ***************************************/

static int win_x0, win_y0, win_wid, win_hgt;


// provide a drawing function
// which "knows" the coordinates and size of the region to draw in
void draw_point( int x, int y, int color) {
  // clip to region
  printf("(%d, %d) %d", x, y, color);
  if( x > 0 && x < win_wid && y > 0 && y < win_wid) {
    fl_point( x + win_x0, y + win_y0, color);
    printf(" -draw\n");
  } else {
    printf(" -skip\n");
  }
}

extern FD_watch_top *fd;

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

  printf("window @ (%d,%d) wid=%d hgt=%d\n", win_x0, win_y0, win_wid, win_hgt);

  dl_setup( draw_point, win_x0, win_x0+win_wid, win_y0, win_y0+win_hgt);

  minutes = fl_get_slider_value( fd->s_min);
  hours = fl_get_slider_value( fd->s_hour);

  fl_rectf( win_x0, win_y0, win_wid, win_hgt, FL_WHITE);

  dl_draw_from_list( FL_RED, clock_tics);
  // index into minutes
  

  int szm = sizeof(clock_minutes)/60; /* size of one minute in bytes */
  b_point* ptm = clock_minutes + minutes * szm; /* point to start */
  dl_draw_from_list( FL_BLUE, ptm);
  // adjust hours from 0..12 to 0..60
  hours = (hours%12)*5 + (float)(minutes/60.)*5;
  szm = sizeof(clock_hours)/60; /* size of one minute */
  ptm = clock_hours + hours * szm; /* point to start */
  dl_draw_from_list( FL_GREEN, ptm);
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



