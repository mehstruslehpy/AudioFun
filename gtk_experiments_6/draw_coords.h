#ifndef DRAW_COORDS_H
#define DRAW_COORDS_H
#include <cairo.h>
#include <math.h>
//draw the horizontal lines of the grid
void draw_horiz_lines(cairo_t* cr,int hcount,int x_bound, int y_bound);
//draw the vertical lines of the grid
void draw_vert_lines(cairo_t* cr,int vcount,int x_bound, int y_bound);
//draw full coordinate system
void draw_coords(cairo_t* cr,int x_bound, int y_bound, int hcount, int vcount);
#endif
