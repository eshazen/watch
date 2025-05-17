//
// clock face drawing
//
#include "display_list.h"

#define F_WIDTH 200
#define F_HEIGHT 200
#define CTR_X (F_WIDTH/2)
#define CTR_Y (F_HEIGHT/2)
#define OUTER_RADIUS (0.95*(F_WIDTH/2))


void display_clock_face(draw_func);
void display_clock_hands(draw_func);

