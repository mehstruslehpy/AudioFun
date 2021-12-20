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
	GtkDrawingArea* drawing_area;
} Context;

//callback that handles mouse click
gboolean on_button(GtkWidget *widget, GdkEventButton  *event, gpointer   user_data)
{
	static Rectangle rect;
	Context context = *((Context*)user_data);
	if (event->type==GDK_BUTTON_PRESS)
	{
		printf("Button pressed at: (%f,%f)\n",event->x,event->y);
		rect.x1 = event->x;
		rect.y1 = event->y;
	}
	else if (event->type==GDK_BUTTON_RELEASE)
	{
		printf("Button released at: (%f,%f)\n",event->x,event->y);
		rect.x2=event->x;
		rect.y2=event->y;
		printf("draw rectangle: (%d,%d)   (%d,%d)\n\n",rect.x1,rect.y1,rect.x2,rect.y2);

		//compute width/height of each division of the screen into the grid
		float w = ((float)WIDTH)/((float)HCOUNT);
		float h = ((float)HEIGHT)/((float)VCOUNT);
		//snap the current rectangle to the grid points of the screen
		snapped_rect_to_grid(&rect,w,h);
		//offset coordinates of rectangle to something nice
		if (rect.x1<rect.x2&&rect.y1>rect.y2) //mouse press->release starts bottom left ends top right
		{
			rect.y1+=h;
			rect.x2+=w;
		}
		else if (rect.x1>=rect.x2&&rect.y1>rect.y2) //from bottom right to top left
		{//
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
		//TODO: Add checking algorithm that removes rectangle if it overlaps any that already exist in the stack
		push(rect,context.rectangle_stack);
		//draw the rectangle
		//on_draw(context.drawing_area,event,&rect);
		on_draw(context.drawing_area,event,context.rectangle_stack);
	}
	return TRUE;
}

//from https://stackoverflow.com/questions/57699050/how-to-create-a-cairo-object-within-a-gtk-window-in-gtk3#58870107
// ------------------------------------------------------------
gboolean on_draw (GtkWidget *widget, GdkEventExpose *event, gpointer data) 
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

// ------------------------------------------------------------

int main (int argc, char * argv[]) {
	Context context = {.rectangle_stack=NULL,.drawing_area=NULL};
	RectStack rectangles = {.top=NULL};
	context.rectangle_stack = &rectangles;
	gtk_init(&argc, &argv);
	GtkWindow * window; 
	{ // window setup
		window = (GtkWindow*)gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_window_set_default_size (window, WIDTH, HEIGHT);
		gtk_window_set_position     (window, GTK_WIN_POS_CENTER);
		gtk_window_set_title        (window, "Drawing");
		g_signal_connect(window, "destroy", gtk_main_quit, NULL);
		gtk_widget_add_events(window, GDK_BUTTON_PRESS_MASK); //enable key press mask on window
		gtk_widget_add_events(window, GDK_BUTTON_RELEASE_MASK); //enable key release mask on window
	}  

	// create the area we can draw in
	GtkDrawingArea* drawingArea;
	{
		drawingArea = (GtkDrawingArea*) gtk_drawing_area_new();
		gtk_container_add(GTK_CONTAINER(window), (GtkWidget*)drawingArea);
		//g_signal_connect((GtkWidget*)drawingArea, "draw", G_CALLBACK(on_draw), &rect);    
		g_signal_connect((GtkWidget*)drawingArea, "draw", G_CALLBACK(on_draw), &rectangles);    
	}  
	context.drawing_area = drawingArea;

	//set up mouse button press and release signals
	g_signal_connect(window, "button-press-event", G_CALLBACK(on_button), &context); //set up button press signal
	g_signal_connect(window, "button-release-event", G_CALLBACK(on_button), &context); //set up button release signal
	
	gtk_widget_show_all ((GtkWidget*)window);
	gtk_main();

	printf("DON'T FORGET TO FREE THE RECTANGLE STACK!\n");
	deallocate(&rectangles);
	return 0;
}

