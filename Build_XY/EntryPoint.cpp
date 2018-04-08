#include "Utilities.h"
#include "GraphDisplay.h"

int main()
{
	initOperations();
	string input;
	fin() >> input;
	FuncYX func = FuncYX(Expression(input));
	GraphDisplay display(900, 900, func, Color::White, Color::Black, Color::Blue);
	display.run();
	return 0;
}