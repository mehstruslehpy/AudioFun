#include "draw_coords.h"
//TODO: the horizontal/vertical functions here are backwards, draw_horiz draws vertical lines and vice versa on accident
void draw_coords(cairo_t* cr,int x_bound,int y_bound,int hcount,int vcount)
{
	//save old ctm so we can fill whole background with white
	cairo_matrix_t temp;
	cairo_get_matrix(cr,&temp);	

	/* fill background white  */
	cairo_identity_matrix(cr);
	cairo_rectangle (cr, 0, 0, x_bound, y_bound);
	cairo_set_source_rgb (cr, 1, 1, 1);
	cairo_fill (cr);

	//restore current ctm
	cairo_set_matrix(cr,&temp);	

	/* draw horizontal grid lines */
	draw_horiz_lines(cr,hcount,x_bound,y_bound);

	/* draw vertical grid lines */
	draw_vert_lines(cr,vcount,x_bound,y_bound);

	/* draw red outline */
	cairo_rectangle (cr, 0, 0, x_bound, y_bound);
	cairo_set_source_rgb (cr, 1, 0, 0);
	cairo_stroke (cr);
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
