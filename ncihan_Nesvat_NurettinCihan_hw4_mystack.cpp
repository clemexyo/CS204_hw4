#include "ncihan_Nesvat_NurettinCihan_hw4_mystack.h"

Stack::Stack():
	top(nullptr) 
{}

void Stack::push(cellStruct c)
{
	cellStruct* newNode = new cellStruct();
	*newNode = c;

	if(isEmpty())
	{
		top = newNode;
	}
	else
	{
		newNode->next = top;
		top = newNode;
	}
}

cellStruct Stack::pop()
{
	cellStruct c;
	cellStruct* temp;
	if(!isEmpty())
	{
		temp = top->next;
		c = *top;
		delete top;
		top = temp;
	}
	return c;
}

bool Stack::isEmpty()
{
	bool empty = true;
	if(top != nullptr)
		empty = false;
	return empty;
}

Stack::~Stack()
{
	if(!isEmpty())
	{
		cellStruct* hold;
		while(top != nullptr)
		{
			hold = top->next;
			delete top;
			top = hold;
		}
	}
}