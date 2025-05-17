
#include <stdio.h>

#include "test.c"

unsigned char* print_list( unsigned char *p) {
  while( p[2] != 255) {
    printf("(%d,%d) %d\n", p[0], p[1], p[2]);
    p += 3;
  }
  return p+3;
}

int main( int argc, char *argv[]) {
  printf("\nclock_tics = \n");
  print_list( clock_tics);
  printf("\nMinute hand:\n");
  unsigned char *p = clock_minutes;
  for( int i=0; i<60; i++) {
    printf("--- Minute: %d\n", i);
    p = print_list( p);
  }
  printf("\nHour hand:\n");
  p = clock_hours;
  for( int i=0; i<60; i++) {
    printf("--- Hour: %d\n", i);
    p = print_list( p);
  }
}
