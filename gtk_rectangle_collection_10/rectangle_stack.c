#include "rectangle_stack.h"

void push(Rectangle rect, RectStack* stk_ptr)
{
	pushNode(makeNode(rect),stk_ptr);
}
void pop(Rectangle* rect, RectStack* stk_ptr)
{
	RNode* node_ptr;
	popNode(&node_ptr,stk_ptr);
	*rect = node_ptr->info;
	free(node_ptr);
}
RNode* makeNode(Rectangle rect)
{
	RNode* p;
	if ((p=(RNode*)malloc(sizeof(RNode)))==NULL)
		printf("ERROR: Exhausted memory for stack.\n");
	else
	{
		p->info = rect;
		p->next = NULL;
	}
	return p;
}
void pushNode(RNode* node_ptr, RectStack* stk_ptr)
{
	if (node_ptr==NULL)
		printf("ERROR: Push to nonexistent node.\n");
	else
	{
		node_ptr->next = stk_ptr->top;
		stk_ptr->top = node_ptr;
	}
}
void popNode(RNode** node_ptr, RectStack* stk_ptr)
{
	if (stk_ptr->top==NULL)
		printf("ERROR: Empty stack.\n");
	else
	{
		*node_ptr = stk_ptr->top;
		stk_ptr->top = (*node_ptr)->next;
	}
}
void deallocate(RectStack *ptr)
{
	Rectangle temp;
	while (ptr->top!=NULL) pop(&temp,ptr);
}

//void remove_intersecting(RNode rn, Rectangle rect);
