#include <cairo.h>
#include <math.h>
#define HCOUNT 88
#define VCOUNT 88
#define HORIZ 4096
#define VERT 4096

//draw the horizontal lines of the grid
void draw_horiz_lines(cairo_t* cr,int hcount,int x_bound, int y_bound);
//draw the vertical lines of the grid
void draw_vert_lines(cairo_t* cr,int vcount,int x_bound, int y_bound);

int main (int argc, char *argv[])
{
	//set up surface and context
	cairo_surface_t *surface =
		cairo_image_surface_create(CAIRO_FORMAT_RGB24, HORIZ, VERT);
	cairo_t *cr =
		cairo_create(surface);

	/* fill background white  */
	cairo_set_source_rgb (cr, 255, 255, 255);
	cairo_rectangle (cr, 0, 0, HORIZ, VERT);
	cairo_fill (cr);

	/*draw diagonal*/
	/*
	cairo_set_source_rgb (cr, 0, 0, 0); //set source to black for lines
	cairo_move_to (cr, 0, 0);
	cairo_rel_line_to (cr, HORIZ, VERT);
	cairo_stroke (cr);
	*/

	/* draw horizontal grid lines */
	draw_horiz_lines(cr,HCOUNT,HORIZ,VERT);

	/* draw vertical grid lines */
	draw_vert_lines(cr,VCOUNT,HORIZ,VERT);

	/* clean up surface and context */
	cairo_destroy(cr);
	cairo_surface_write_to_png(surface, "cairo-rectangles.png");
	cairo_surface_destroy(surface);
	return 0;
}

void draw_horiz_lines(cairo_t* cr,int hcount,int x_bound, int y_bound)
{
	cairo_set_source_rgb (cr, 0, 0, 0); //set source to black for lines
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
	cairo_set_source_rgb (cr, 0, 0, 0); //set source to black for lines
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
