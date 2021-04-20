#ifndef _MY_STACK_H
#define _MY_STACK_H

struct cellStruct
{
	char info;
	bool flag;
	cellStruct* next;
	int row_index;
	int col_index;
	

	cellStruct(): //default constructor
		info('-'),
		row_index(0),
		col_index(0),
		next(nullptr),
		flag(false)
	{}

	cellStruct(char inf, int row, int col): //three parameters constructor
		info(inf), 
		row_index(row), 
		col_index(col), 
		flag(false), 
		next(nullptr)
	{}
};

class Stack
{
private:
	cellStruct* top;
public:
	Stack(); //class constructor
	~Stack(); //class destructor
	void push(cellStruct);
	cellStruct pop();
	bool isEmpty();
};

#endif