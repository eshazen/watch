#include "watch.h"

FD_watch_top *fd;

int
main( int    argc,
      char * argv[ ] )
{

    fl_initialize( &argc, argv, 0, 0, 0 );
    fd = create_form_watch_top( );
    /* Fill-in form initialization code */

    /* Show the first form */

    fl_show_form( fd->watch_top, FL_PLACE_CENTERFREE, FL_FULLBORDER, "watch_top" );

    fl_do_forms( );

    if ( fl_form_is_visible( fd->watch_top ) )
        fl_hide_form( fd->watch_top );
    fl_free( fd );
    fl_finish( );

    return 0;
}
