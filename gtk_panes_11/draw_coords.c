#include "draw_coords.h"

void draw_coords(cairo_t* cr,int x_bound,int y_bound,int hcount,int vcount)
{
	//set up surface and context
	cairo_surface_t *surface =
		cairo_image_surface_create(CAIRO_FORMAT_RGB24, x_bound, y_bound);

	/* fill background white  */
	cairo_set_source_rgb (cr, 1, 1, 1);
	cairo_rectangle (cr, 0, 0, x_bound, y_bound);
	cairo_fill (cr);

	/* draw horizontal grid lines */
	draw_horiz_lines(cr,hcount,x_bound,y_bound);

	/* draw vertical grid lines */
	draw_vert_lines(cr,vcount,x_bound,y_bound);

	/* clean up surface and context */
	//cairo_destroy(cr);
	//cairo_surface_write_to_png(surface, "cairo-rectangles.png");
	cairo_surface_destroy(surface);
}

void draw_horiz_lines(cairo_t* cr,int hcount,int x_bound, int y_bound)
{
	cairo_set_source_rgb (cr, 0.75, 0.75, 0.75); //set source to gray for lines
	//cairo_set_line_width (cr, 6.0);
	double hincr = (float)x_bound/(float)hcount;
	cairo_move_to (cr, 0, 0);
	cairo_line_to (cr, 0, y_bound);
	cairo_stroke (cr);
	double x=hincr;
	for (int i=0;i<hcount;i++)
	{
		cairo_move_to (cr, x, 0);
		cairo_line_to (cr, x, y_bound);
		cairo_stroke (cr);
		x+=hincr;
	}
}

void draw_vert_lines(cairo_t* cr,int vcount,int x_bound, int y_bound)
{
	cairo_set_source_rgb (cr, 0.75, 0.75, 0.75); //set source to gray for lines
	//cairo_set_line_width (cr, 6.0);
	double vincr = (float)y_bound/(float)vcount;
	cairo_move_to (cr, 0, 0);
	cairo_line_to (cr, x_bound, 0);
	cairo_stroke (cr);
	double y=vincr;
	for (int i=0;i<vcount;i++)
	{
		cairo_move_to (cr, 0, y);
		cairo_line_to (cr, x_bound, y);
		cairo_stroke (cr);
		y+=vincr;
	}
}
