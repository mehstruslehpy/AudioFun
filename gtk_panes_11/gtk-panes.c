#include <gtk/gtk.h>
#include <cairo.h>
#include "draw_coords.h"
//#include "draw_rectangles.h"
#include "rectangle_stack.h"
//width of screen
#define WIDTH 1024
//height of screen
#define HEIGHT 650 
//grid divisions of screen
#define HCOUNT 24
#define VCOUNT 48

//passed to callbacks, contains drawing area and rectangles to be drawn
typedef struct context
{
	RectStack* rectangle_stack;
	GtkDrawingArea* note_drawing_area;
	GtkDrawingArea* velocity_drawing_area;
} Context;

gboolean velocity_button(GtkWidget *widget, GdkEventButton  *event, gpointer   user_data)
{
	static Rectangle rect;
	Context context = *((Context*)user_data);

	//left mouse button press
	if (event->type==GDK_BUTTON_PRESS)
	{
		printf("Velocity window left button pressed at: (%f,%f)\n",event->x,event->y);
		rect.x1 = event->x;
		rect.y1 = event->y;

		RNode* rn = context.rectangle_stack->top;

		float w = ((float)WIDTH)/((float)HCOUNT);
		while (rn!=NULL)
		{
			if (rect.x1>=rn->info.x1 && rect.x1<=rn->info.x1+w)
				rn->info.vel = (float)(HEIGHT-rect.y1)/(float)HEIGHT;
			rn=rn->next;
		}

		//redraw
		note_draw(context.note_drawing_area,event,context.rectangle_stack);
		velocity_draw(context.velocity_drawing_area,event,context.rectangle_stack);

	}
	return TRUE;
}
//callback that handles mouse click in the note drawing area
gboolean note_button(GtkWidget *widget, GdkEventButton  *event, gpointer   user_data)
{
	static Rectangle rect;
	Context context = *((Context*)user_data);

	//right mouse button press
	if ((event->button==2||event->button==3)&&event->type==GDK_BUTTON_PRESS)
	{
		printf("Note window right button press at: (%f,%f)\n",event->x,event->y);
		remove_rectangles_containing_point(context.rectangle_stack,event->x,event->y);
		note_draw(context.note_drawing_area,event,context.rectangle_stack);
		velocity_draw(context.velocity_drawing_area,event,context.rectangle_stack);
		return TRUE;
	} //right mouse button release
	else if ((event->button==2||event->button==3)&&event->type==GDK_BUTTON_RELEASE)
	{
		return TRUE;
	}

	//left mouse button press
	if (event->type==GDK_BUTTON_PRESS)
	{
		printf("Note window left button pressed at: (%f,%f)\n",event->x,event->y);
		rect.x1 = event->x;
		rect.y1 = event->y;
		rect.vel = 1;
	}
	else if (event->type==GDK_BUTTON_RELEASE)
	{
		printf("Note window left button released at: (%f,%f)\n",event->x,event->y);
		rect.x2=event->x;
		rect.y2=event->y;
		printf("draw rectangle: (%f,%f)   (%f,%f)\n",rect.x1,rect.y1,rect.x2,rect.y2);

		//compute width/height of each division of the screen into the grid
		float w = ((float)WIDTH)/((float)HCOUNT);
		float h = ((float)HEIGHT)/((float)VCOUNT);

		//snap the current rectangle to the grid points of the screen
		snapped_rect_to_grid(&rect,w,h);

		if (rect.x1<rect.x2&&rect.y1>rect.y2) //mouse press->release starts bottom left ends top right
		{
			rect.y1+=h;
			rect.x2+=w;
		}
		else if (rect.x1>=rect.x2&&rect.y1>rect.y2) //from bottom right to top left
		{
			rect.x1+=w;
			rect.y1+=h;
		}
		else if (rect.x1<rect.x2&&rect.y1<=rect.y2) //top left to bottom right
		{
			rect.y2+=h;
			rect.x2+=w;
		}
		else if (rect.x1>=rect.x2&&rect.y1<=rect.y2) //from top right to bottom left
		{
			rect.x1+=w;
			rect.y2+=h;
		}
		//Note: For audio we only need rectangles with height=1 block
		rect.y2=rect.y1+h;

		//push rectangle to stack
		push(rect,context.rectangle_stack);
		//draw the rectangle
		note_draw(context.note_drawing_area,event,context.rectangle_stack);
		velocity_draw(context.velocity_drawing_area,event,context.rectangle_stack);
	}
	return TRUE;
}

//from https://stackoverflow.com/questions/57699050/how-to-create-a-cairo-object-within-a-gtk-window-in-gtk3#58870107
// ------------------------------------------------------------
gboolean note_draw (GtkWidget *widget, GdkEventExpose *event, gpointer data) 
{
	// "convert" the G*t*kWidget to G*d*kWindow (no, it's not a GtkWindow!)
	GdkWindow* window = gtk_widget_get_window(widget);  

	cairo_region_t * cairoRegion = cairo_region_create();

	GdkDrawingContext * drawingContext;
	drawingContext = gdk_window_begin_draw_frame (window,cairoRegion);

	{ 
		// say: "I want to start drawing"
		cairo_t * cr = gdk_drawing_context_get_cairo_context (drawingContext);

		{ // do your drawing
			draw_coords(cr,WIDTH,HEIGHT,HCOUNT,VCOUNT);
			//draw_rectangle(cr,rect.x1,rect.y1,rect.x2,rect.y2);
			RectStack stk = *((RectStack*)data);
			RNode* rn = stk.top;

			//compute width/height of each division of the screen into the grid
			while (rn!=NULL)
			{
				draw_rectangle(cr,rn->info.x1,rn->info.y1,rn->info.x2,rn->info.y2);
				rn=rn->next;
			}
		}

		// say: "I'm finished drawing
		gdk_window_end_draw_frame(window,drawingContext);
	}

	// cleanup
	cairo_region_destroy(cairoRegion);

	return FALSE;
}
gboolean velocity_draw(GtkWidget *widget, GdkEventExpose *event, gpointer data) 
{
	// "convert" the G*t*kWidget to G*d*kWindow (no, it's not a GtkWindow!)
	GdkWindow* window = gtk_widget_get_window(widget);  

	cairo_region_t * cairoRegion = cairo_region_create();

	GdkDrawingContext * drawingContext;
	drawingContext = gdk_window_begin_draw_frame (window,cairoRegion);

	{ 
		// say: "I want to start drawing"
		cairo_t * cr = gdk_drawing_context_get_cairo_context (drawingContext);

		{ // do your drawing
			draw_coords(cr,WIDTH,HEIGHT,HCOUNT,VCOUNT);
			//draw_rectangle(cr,rect.x1,rect.y1,rect.x2,rect.y2);
			RectStack stk = *((RectStack*)data);
			RNode* rn = stk.top;
			float w = ((float)WIDTH)/((float)HCOUNT);
			while (rn!=NULL)
			{
				draw_rectangle(cr,rn->info.x1,HEIGHT,rn->info.x1+w,HEIGHT*(1-rn->info.vel));
				rn=rn->next;
			}
		}

		// say: "I'm finished drawing
		gdk_window_end_draw_frame(window,drawingContext);
	}

	// cleanup
	cairo_region_destroy(cairoRegion);

	return FALSE;
}
// ------------------------------------------------------------

int main (int argc, char * argv[]) {
	//variables about drawing area and rectangle stack
	Context context = {.rectangle_stack=NULL,.note_drawing_area=NULL,.velocity_drawing_area=NULL};
	RectStack rectangles = {.top=NULL};
	context.rectangle_stack = &rectangles;

	gtk_init(&argc, &argv);

	// window setup
	GtkWindow * window; 
	window = (GtkWindow*)gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(window, "Drawing");
	g_signal_connect(window, "destroy", gtk_main_quit, NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window),10);
	gtk_widget_set_size_request(window,WIDTH,HEIGHT);

	// create the note drawing area
	GtkDrawingArea* noteDrawingArea;
	noteDrawingArea = (GtkDrawingArea*) gtk_drawing_area_new();
	g_signal_connect((GtkWidget*)noteDrawingArea, "draw", G_CALLBACK(note_draw), &rectangles);    
	gtk_widget_add_events(noteDrawingArea, GDK_BUTTON_PRESS_MASK); //enable key press mask
	gtk_widget_add_events(noteDrawingArea, GDK_BUTTON_RELEASE_MASK); //enable key release mask

	// create the velocity drawing area
	GtkDrawingArea* velocityDrawingArea;
	velocityDrawingArea = (GtkDrawingArea*) gtk_drawing_area_new();
	g_signal_connect((GtkWidget*)velocityDrawingArea, "draw", G_CALLBACK(velocity_draw), &rectangles);    
	gtk_widget_add_events(velocityDrawingArea, GDK_BUTTON_PRESS_MASK); //enable key press mask

	//set up drawing area in context
	context.note_drawing_area = noteDrawingArea;
	context.velocity_drawing_area = velocityDrawingArea;

	//set up mouse button press and release signals
	g_signal_connect(noteDrawingArea,
					"button-press-event",
					G_CALLBACK(note_button), 
					&context); //set up button press signal
	g_signal_connect(noteDrawingArea,
					"button-release-event", 
					G_CALLBACK(note_button), 
					&context); //set up button release signal
	g_signal_connect(velocityDrawingArea,
					"button-press-event",
					G_CALLBACK(velocity_button),
					&context); //set up button press signal

	//pane widget setup
	GtkWidget *vpaned = gtk_vpaned_new();
	gtk_paned_add1(GTK_PANED(vpaned),noteDrawingArea);
	gtk_paned_add2(GTK_PANED(vpaned),velocityDrawingArea);
	gtk_paned_set_position(vpaned, HEIGHT/2);
	gtk_paned_set_wide_handle(vpaned, TRUE);
	gtk_container_add(GTK_CONTAINER(window), vpaned);
	
	gtk_widget_show_all ((GtkWidget*)window);
	gtk_main();
	deallocate(&rectangles);

	return 0;
}

