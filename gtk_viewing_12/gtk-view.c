#include <gtk/gtk.h>
#include <cairo.h>
#include "draw_coords.h"
//#include "draw_rectangles.h"
#include "rectangle_stack.h"

//passed to callbacks, contains drawing area, rectangles to be drawn and pan/zoom amounts
typedef struct context
{
	RectStack* rectangle_stack;
	GtkDrawingArea* note_drawing_area;
	GtkDrawingArea* velocity_drawing_area;
	int width; //width of the model
	int height; //height of the model
	int hcount; //horizontal grid divisions of the model
	int vcount; //vertical grid divisions of the model
	double zoom; //zoom amount
	double pan_x; //x panning amount
	double pan_y; //y panning amount
} Context;

gboolean pan_zoom_key(GtkWidget *widget, GdkEventKey  *event, gpointer   user_data)
{
	Context* context = ((Context*)user_data);
	if (event->type==GDK_KEY_PRESS && event->keyval==GDK_KEY_Up)
	{
		printf("Up key pressed.\n");
		context->pan_y+=50;
	}
	else if (event->type==GDK_KEY_PRESS && event->keyval==GDK_KEY_Down)
	{
		printf("Down key pressed.\n");
		context->pan_y-=50;
	}
	else if (event->type==GDK_KEY_PRESS && event->keyval==GDK_KEY_Left)
	{
		printf("Left key pressed.\n");
		context->pan_x+=50;
	}
	else if (event->type==GDK_KEY_PRESS && event->keyval==GDK_KEY_Right)
	{
		printf("Right key pressed.\n");
		context->pan_x-=50;
	}
	else if (event->type==GDK_KEY_PRESS && event->keyval==GDK_KEY_i)
	{
		printf("i key pressed.\n");
		context->zoom+=0.1;
	}
	else if (event->type==GDK_KEY_PRESS && event->keyval==GDK_KEY_o)
	{
		printf("o key pressed.\n");
		if (context->zoom>=0.2) context->zoom-=0.1;
	}
	else return TRUE;
	//redraw
	note_draw(context->note_drawing_area,event,context);
	velocity_draw(context->velocity_drawing_area,event,context);
	return TRUE;
}
gboolean velocity_button(GtkWidget *widget, GdkEventButton  *event, gpointer   user_data)
{
	static Rectangle rect;
	Context context = *((Context*)user_data);

	//xform pointer coords to from screen to model coords
	event->x-=context.pan_x;
	//event->y-=context.pan_y;
	event->x/=context.zoom;
	//event->y/=context.zoom;

	//left mouse button press
	if (event->type==GDK_BUTTON_PRESS)
	{
		printf("Velocity window left button pressed at: (%f,%f)\n",event->x,event->y);
		rect.x1 = event->x;
		rect.y1 = event->y;

		RNode* rn = context.rectangle_stack->top;

		float w = ((float)context.width)/((float)context.hcount);
		while (rn!=NULL)
		{
			if (rect.x1>=rn->info.x1 && rect.x1<=rn->info.x1+w)
			{
				printf("Velocity change:\n\tOld velocity: %f\n",rn->info.vel);
				rn->info.vel = (float)(context.height-rect.y1)/(float)context.height;
				printf("\tNew velocity: %f\n",rn->info.vel);
			}
			rn=rn->next;
		}

		//redraw
		note_draw(context.note_drawing_area,event,&context);
		velocity_draw(context.velocity_drawing_area,event,&context);
	
	}
	return TRUE;
}
//callback that handles mouse click in the note drawing area
gboolean note_button(GtkWidget *widget, GdkEventButton  *event, gpointer   user_data)
{
	static Rectangle rect;
	Context context = *((Context*)user_data);

	//xform pointer coords to from screen to model coords
	event->x-=context.pan_x;
	event->y-=context.pan_y;
	event->x/=context.zoom;
	event->y/=context.zoom;
	
	//right mouse button press
	if ((event->button==2||event->button==3)&&event->type==GDK_BUTTON_PRESS)
	{
		printf("Note window right button press at: (%f,%f)\n",event->x,event->y);
		remove_rectangles_containing_point(context.rectangle_stack,event->x,event->y);
		note_draw(context.note_drawing_area,event,&context);
		velocity_draw(context.velocity_drawing_area,event,&context);
		
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
		float w = ((float)context.width)/((float)context.hcount);
		float h = ((float)context.height)/((float)context.vcount);

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
		note_draw(context.note_drawing_area,event,&context);
		velocity_draw(context.velocity_drawing_area,event,&context);
	}
	return TRUE;
}

//from https://stackoverflow.com/questions/57699050/how-to-create-a-cairo-object-within-a-gtk-window-in-gtk3#58870107
// ------------------------------------------------------------
gboolean note_draw (GtkWidget *widget, GdkEventExpose *event, gpointer data) 
{
	Context context = *((Context*)data);
	//"convert" the G*t*kWidget to G*d*kWindow (no, it's not a GtkWindow!)
	GdkWindow* window = gtk_widget_get_window(widget);  

	cairo_region_t * cairoRegion = cairo_region_create();

	GdkDrawingContext * drawingContext;
	drawingContext = gdk_window_begin_draw_frame (window,cairoRegion);

	//set up a cairo context to draw with
	cairo_t * cr = gdk_drawing_context_get_cairo_context (drawingContext);
	
	//Setup pan and zoom
	cairo_translate(cr,context.pan_x,context.pan_y);
	cairo_scale(cr,context.zoom,context.zoom);

	//draw coord lines and etc
	draw_coords(cr,context.width,context.height,context.hcount,context.vcount);

	//draw all rectangles to screen	
	RectStack stk = *(context.rectangle_stack);
	RNode* rn = stk.top;

	while (rn!=NULL)
	{
		draw_rectangle(cr,rn->info.x1,rn->info.y1,rn->info.x2,rn->info.y2,0,rn->info.vel,1-rn->info.vel);
		rn=rn->next;
	}

	//end drawing
	gdk_window_end_draw_frame(window,drawingContext);

	// cleanup
	cairo_region_destroy(cairoRegion);

	return FALSE;
}
gboolean velocity_draw(GtkWidget *widget, GdkEventExpose *event, gpointer data) 
{
	Context context = *((Context*)data);
	// "convert" the G*t*kWidget to G*d*kWindow (no, it's not a GtkWindow!)
	GdkWindow* window = gtk_widget_get_window(widget);  

	cairo_region_t * cairoRegion = cairo_region_create();

	GdkDrawingContext * drawingContext;
	drawingContext = gdk_window_begin_draw_frame (window,cairoRegion);

	//set up cairo context to draw with
	cairo_t * cr = gdk_drawing_context_get_cairo_context (drawingContext);

	//Setup pan and zoom
	//cairo_translate(cr,context.pan_x,context.pan_y);
	cairo_translate(cr,context.pan_x,0);
	//cairo_scale(cr,context.zoom,context.zoom);
	cairo_scale(cr,context.zoom,1);

	//draw coord grid lines
	draw_coords(cr,context.width,context.height,context.hcount,context.vcount);

	//draw rectangles
	RectStack stk = *(context.rectangle_stack);
	RNode* rn = stk.top;
	float w = ((float)context.width)/((float)context.hcount);
	while (rn!=NULL)
	{
		//draw_rectangle(cr,rn->info.x1,HEIGHT,rn->info.x1+w,HEIGHT*(1-rn->info.vel));
		//this version draws velocity rectangles with a width of 15 pixels
		draw_rectangle(cr,rn->info.x1,context.height,rn->info.x1+15,context.height*(1-rn->info.vel),0,rn->info.vel,1-rn->info.vel);
		rn=rn->next;
	}

	//end drawing
	gdk_window_end_draw_frame(window,drawingContext);

	// cleanup
	cairo_region_destroy(cairoRegion);

	return FALSE;
}
// ------------------------------------------------------------
int main (int argc, char * argv[]) {
	//variables about drawing area and rectangle stack
	Context context = {
						.rectangle_stack=NULL,
						.note_drawing_area=NULL,
						.velocity_drawing_area=NULL,
						.width=1024,
						.height=650,
						.hcount=24,
						.vcount=48,
						.pan_x=1,
						.pan_y=1,
						.zoom=1
	};
	RectStack rectangles = {.top=NULL};
	context.rectangle_stack = &rectangles;

	gtk_init(&argc, &argv);

	// window setup
	GtkWindow * window; 
	window = (GtkWindow*)gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(window, "Drawing");
	g_signal_connect(window, "destroy", gtk_main_quit, NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window),10);
	gtk_widget_set_size_request(window,context.width,context.height);
	gtk_widget_add_events(window, GDK_KEY_PRESS_MASK); //enable key press mask

	// create the note drawing area
	GtkDrawingArea* noteDrawingArea;
	noteDrawingArea = (GtkDrawingArea*) gtk_drawing_area_new();
	gtk_widget_add_events(noteDrawingArea, GDK_BUTTON_PRESS_MASK); //enable key press mask
	gtk_widget_add_events(noteDrawingArea, GDK_BUTTON_RELEASE_MASK); //enable key release mask

	// create the velocity drawing area
	GtkDrawingArea* velocityDrawingArea;
	velocityDrawingArea = (GtkDrawingArea*) gtk_drawing_area_new();
	gtk_widget_add_events(velocityDrawingArea, GDK_BUTTON_PRESS_MASK); //enable key press mask

	//set up drawing area in context
	context.note_drawing_area = noteDrawingArea;
	context.velocity_drawing_area = velocityDrawingArea;
	
	//pane widget setup
	GtkWidget *vpaned = gtk_vpaned_new();
	gtk_paned_add1(GTK_PANED(vpaned),noteDrawingArea);
	gtk_paned_add2(GTK_PANED(vpaned),velocityDrawingArea);
	gtk_paned_set_position(vpaned, context.height/2);
	gtk_paned_set_wide_handle(vpaned, TRUE);
	gtk_container_add(GTK_CONTAINER(window), vpaned);
	
	//set up mouse button press and release signals
	g_signal_connect((GtkWidget*)noteDrawingArea, "draw", G_CALLBACK(note_draw), &context);    
	g_signal_connect((GtkWidget*)velocityDrawingArea, "draw", G_CALLBACK(velocity_draw), &context);    
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
	g_signal_connect(window,
					"key-press-event",
					G_CALLBACK(pan_zoom_key), 
					&context); //set up button press signal

	gtk_widget_show_all ((GtkWidget*)window);
	gtk_main();
	deallocate(&rectangles);

	return 0;
}

