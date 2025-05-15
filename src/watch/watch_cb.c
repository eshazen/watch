#include "watch.h"

/* Callbacks and freeobj handles for form watch_top */

/***************************************
 ***************************************/

extern FD_watch_top *fd;

void cb_clock( FL_OBJECT * ob,
         long        data )
{
  // get coordinates of screen
  FL_Coord x, y, w, h;
  fl_get_object_geometry( fd->screen, &x, &y, &w, &h);

  fl_line( x, y, x+w, y+h, FL_RED);
}




