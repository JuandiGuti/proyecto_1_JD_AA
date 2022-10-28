#include "stack.h"
#include <string>
using namespace std;

stack::stack(int max)
{
	indextop = -1;
	maxsize = max;
	arr = new string[max];
}

int stack::size() const
{
	return indextop + 1;
}

bool stack::is_empty() const
{
	return (indextop == -1);
}

string stack::top() const
{
	return arr[indextop];
}

void stack::push(string dat)
{
	if (indextop + 1 < maxsize) {
		arr[++indextop] = dat;
	}
}

void stack::pop()
{
	if (!is_empty()) {
		indextop--;
	}
}

stack::~stack()
{
	delete[]arr;
}

