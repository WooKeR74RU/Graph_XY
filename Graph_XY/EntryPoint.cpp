#include "Utilities.h"
#include "GraphDisplay.h"
#include "Colors.h"

int main()
{
	const int sWidth = 900;
	const int sHeight = 900;
	const Color colorBackground = Color::White;
	const Color colorAxes = Color::Black;

	initOperations();
	initColors();

	int n;
	fin() >> n;
	vector<pair<Function, Color>> funcs;
	for (int i = 0; i < n; i++)
	{
		string expr, color;
		fin() >> expr >> color;
		bool isYFunc = expr[0] == 'y';
		bool isXFunc = expr[0] == 'x';
		expr.erase(expr.begin(), expr.begin() + 2);
		if (isYFunc)
			funcs.push_back(make_pair(Function(Expression(expr), "x"), getColor(color)));
		if (isXFunc)
			funcs.push_back(make_pair(Function(Expression(expr), "y"), getColor(color)));
	}
	GraphDisplay display(sWidth, sHeight, funcs, colorBackground, colorAxes);
	display.start();

	return 0;
}