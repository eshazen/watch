#include "watch.h"


/***************************************
 ***************************************/

int
main( int    argc,
      char * argv[ ] )
{
    FD_watch_top *fd_watch_top;

    fl_initialize( &argc, argv, 0, 0, 0 );
    fd_watch_top = create_form_watch_top( );

    /* Fill-in form initialization code */

    /* Show the first form */

    fl_show_form( fd_watch_top->watch_top, FL_PLACE_CENTERFREE, FL_FULLBORDER, "watch_top" );

    fl_do_forms( );

    if ( fl_form_is_visible( fd_watch_top->watch_top ) )
        fl_hide_form( fd_watch_top->watch_top );
    fl_free( fd_watch_top );
    fl_finish( );

    return 0;
}
