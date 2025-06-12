//
// parts for clock tables
//

#include "clock_fun.h"

#define DEBUG

int main( int argc, char *argv[]) {

  double min_len = 0.8;		/* length of minute hand */
  double min_wid = 0.1;	        /* width of base */

  double hr_len = 0.5;		/* length of hour hand */
  double hr_wid = 0.2;		/* width of base */

  double qh_tick = 0.85;	/* inner r of quarter hour ticks */
  double hr_tick = 0.95;	/* inner r of hourly ticks */
  double m_tick = 0.98;		/* inner r of minute ticks */

  ps = 0;
  debug = 0;
  npt = 0;
  scale = 99;			/* default for 200x200 display */
  offset = 100;

  d_point p_end = { P_END, 0., 0. };

  for( int i=1; i<argc; i++) {
    if( *argv[i] == '-') {
      switch( toupper( argv[i][1])) {
      case 'H':
	printf("./clock_part -d (debug)\n");
	printf("             -s <scale>\n");
	printf("             -o <offset>\n");
	printf("             -c (C output)\n");
	exit(1);
	break;
      case 'D':
	debug = 1;
	break;
      case 'S':
	++i;
	scale = strtoul( argv[i], NULL, 0);
	break;
      case 'O':
	++i;
	offset = strtoul( argv[i], NULL, 0);
	break;
      default:
	break;
      }
    } else {
      ;
    }
  }

  npt = 0;

  printf("// ----- auto-generated clock display tables -----\n");
  printf("  b_point clock_tics[] = {\n");
  // draw tics
  // first the quarter hours
  for( int i=0; i<=45; i+=15)
    draw_tick( i, qh_tick, 1.);
  // now the hours
  for( int i=5; i<=55; i+=5)
    draw_tick( i, hr_tick, 1.);
  print_point( p_end);
  printf("   };\n");


  // minute hands
  printf("// ----- minute hand, 60 positions -----\n");
  printf("  b_point clock_minutes[] = {\n");
  for( int s=0; s<60; s++) {
    printf("// min_hand_%02d:\n", s);
    //    printf(" {\n");
    draw_hand( s, min_wid, min_len);
    print_point( p_end);
    if( s != 59)
      printf( ",\n");
  }
  printf("   };\n");

  // hour hands
  printf("// ----- hour hand, 60 positions -----\n");
  printf("  b_point clock_hours[] = {\n");
  for( int s=0; s<60; s++) {
    printf("// hr_hand_%02d:\n", s);
    // printf("{\n");
    draw_hand( s, hr_wid, hr_len);
    print_point( p_end);
    if( s != 59)
      printf( ",\n");
  }
  printf("   };\n");


}


