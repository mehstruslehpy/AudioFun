#ifndef RECTANGLE_STACK_
#define RECTANGLE_STACK_
#include "draw_rectangles.h"
#include <stddef.h>
#include <stdio.h>

typedef struct rnode
{
	Rectangle info;
	struct rnode* next;	
} RNode;

typedef struct rect_stack
{
	RNode* top;
} RectStack;

void push(Rectangle rect, RectStack* stk_ptr);
void pop(Rectangle* rect, RectStack* stk_ptr);

RNode* makeNode(Rectangle rect);
void pushNode(RNode* node_ptr, RectStack* stk_ptr);
void popNode(RNode** node_ptr, RectStack* stk_ptr);
void deallocate(RectStack* stk_ptr);
//void remove_intersecting(RNode rn, Rectangle rect);
void remove_rectangles_containing_point(RectStack* stk, float x, float y);
#endif
