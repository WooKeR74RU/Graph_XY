#include "Utilities.h"
#include "GraphDisplay.h"
#include "Colors.h"

int main()
{
	initOperations();
	initColors();

	//string input;
	//fin() >> input;
	//FuncYX func = FuncYX(Expression(input));
	//GraphDisplay display(900, 900, func, Color::White, Color::Black, Color::Blue);
	//display.run();
	//return 0;

	int n;
	fin() >> n;
	vector<pair<FuncYX, Color>> funcs;
	for (int i = 0; i < n; i++)
	{
		string func, color;
		fin() >> func >> color;
		funcs.push_back(make_pair(FuncYX(Expression(func)), getColor(color)));
	}
	GraphDisplay display(900, 900, funcs, Color::White, Color::Black);
	display.run();

	return 0;
}