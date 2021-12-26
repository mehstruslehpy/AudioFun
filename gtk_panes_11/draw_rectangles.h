#ifndef DRAW_RECTANGLE_H
#define DRAW_RECTANGLE_H_
#include <cairo.h>
#include <math.h>
//rectangle type, not really used just here for convenience
typedef struct Rectangle
{
    float x1;
    float y1;
    float x2;
    float y2;
    float vel; //normalized velocity of the given rectangle
} Rectangle;
void draw_rectangle(cairo_t* cr,int x1, int y1, int x2, int y2);
void snapped_rect_to_grid(Rectangle* rect,float width,float height);
#endif
