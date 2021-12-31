#include "rectangle_stack.h"

void push(Rectangle rect, RectStack* stk_ptr)
{
	printf("Node added.\n"); //useful for reference counting
	int temp=0;
	//always force (x1,y1) to be bottom left pt and (x2,y2) to be top right pt in stack
	if (rect.x1>rect.x2 && rect.y1<=rect.y2) //(x1,x2)=bottom right (y1,y2)=top left
	{
		temp = rect.x1;
		rect.x1 = rect.x2;
		rect.x2 = temp;
	}
	else if (rect.x1<=rect.x2 && rect.y1>rect.y2) //(x1,x2)=top left (y1,y2)=bottom right
	{
		temp = rect.y1;
		rect.y1 = rect.y2;
		rect.y2 = temp;
	}
	else if (rect.x1>rect.x2 && rect.y1>rect.y2) //(x1,x2)=top right (y1,y2)=bottom left
	{
		temp = rect.x1;
		rect.x1 = rect.x2;
		rect.x2 = temp;

		temp = rect.y1;
		rect.y1 = rect.y2;
		rect.y2 = temp;
	}
	
	//always force rectangle velocity to be between 0 and 1
	if (rect.vel>1) rect.vel=1;
	else if (rect.vel<0) rect.vel=0;

	//otherwise rectangle on input is already correct
	pushNode(makeNode(rect),stk_ptr);
}
void pop(Rectangle* rect, RectStack* stk_ptr)
{
	printf("Node removed.\n"); //useful for reference counting
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

void remove_rectangles_containing_point(RectStack* stk, float x, float y)
{
	printf("Searching rectangle stack\n");
	if (stk->top==NULL) 
	{
		printf("Rectangle stack empty, nothing to do.\n");
		return; //do nothing on empty stack
	}
	RNode* temp = NULL;
	//base case
	printf("\tChecking rectangle at: (%f,%f)   (%f,%f)\n",
				stk->top->info.x1,
				stk->top->info.y1,
				stk->top->info.x2,
				stk->top->info.y2);
	if (x>=stk->top->info.x1 && y>=stk->top->info.y1
		&&x<=stk->top->info.x2 && y<=stk->top->info.y2)
	{
		printf("\t\tRemoving\n");
		temp = stk->top;
		stk->top=stk->top->next;
		free(temp);
		printf("Node removed.\n"); //useful for reference counting
	}
	else
		printf("\t\tLeaving\n");
	if (stk->top==NULL) return;
		
	//inductive step
	RNode* rn = stk->top;
	while (rn->next!=NULL)
	{
		printf("\tChecking rectangle at: (%f,%f)   (%f,%f)\n",
				rn->next->info.x1,
				rn->next->info.y1,
				rn->next->info.x2,
				rn->next->info.y2);
		if (x>=rn->next->info.x1 && y>=rn->next->info.y1
			&&x<=rn->next->info.x2 && y<=rn->next->info.y2)
		{
			printf("\t\tRemoving\n");
			temp = rn->next;
			rn->next=rn->next->next;
			free(temp);
			printf("Node removed.\n"); //useful for reference counting
		}
		else
		{
			printf("\t\tLeaving\n");
			rn=rn->next;
		}
	}
}
