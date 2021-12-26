#include "draw_rectangles.h"

void snapped_rect_to_grid(Rectangle* rect,float width,float height)
{
	rect->x1 = width*floorf(rect->x1/width);
	rect->y1 = height*floorf(rect->y1/height);
	rect->x2 = width*floorf(rect->x2/width);
	rect->y2 = height*floorf(rect->y2/height);
}
void draw_rectangle(cairo_t* cr,int x1,int y1,int x2,int y2)
{
	//draw outline
	cairo_set_source_rgb (cr, 0, 1, 0);
	//line 1
	cairo_move_to(cr, x1, y1);
	cairo_line_to(cr, x1, y2);
	cairo_line_to(cr, x2, y2);
	cairo_line_to(cr, x2, y1);
	cairo_close_path (cr);
	cairo_fill_preserve (cr);

	//draw outline
	cairo_set_source_rgb (cr, 0, 0, 0);
	//line 1
	cairo_move_to(cr, x1, y1);
	cairo_line_to(cr, x1, y2);
	cairo_stroke(cr);
	//line 2
	cairo_move_to(cr, x1, y1);
	cairo_line_to(cr, x2, y1);
	cairo_stroke(cr);
	//line 3
	cairo_move_to(cr, x1, y2);
	cairo_line_to(cr, x2, y2);
	cairo_stroke(cr);
	//line 4
	cairo_move_to(cr, x2, y1);
	cairo_line_to(cr, x2, y2);
	cairo_stroke(cr);

}
