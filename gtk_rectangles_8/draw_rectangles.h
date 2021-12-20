#ifndef DRAW_RECTANGLE_H
#define DRAW_RECTANGLE_H_
#include <cairo.h>
#include <math.h>
//rectangle type, not really used just here for convenience
typedef struct Rectangle
{
    int x1;
    int y1;
    int x2;
    int y2;
} Rectangle;
void draw_rectangle(cairo_t* cr,int x1, int y1, int x2, int y2);
#endif
