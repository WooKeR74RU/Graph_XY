#include "Utilities.h"
#include "FuncYX.h"
#include <iostream>

//Configuration
const int sW = 900, sH = 900;

//Colors
Color colorBackground;
Color colorAxes;
Color colorGraph;
Color colorText;
void initColors()
{
	colorBackground = Color::Black;
	colorAxes = Color::White;
	colorGraph = Color::Red;
	colorText = Color::Cyan;
}

double offsetX = 0;
double offsetY = 0;
double scale = 14;

bool onScreen(int cX, int cY)
{
	return 0 <= cX && cX < sW && 0 <= cY && cY < sH;
}
double toMathX(int x)
{
	return (x - sW / 2) / scale + offsetX;
}
double toMathY(int y)
{
	return -(y - sH / 2) / scale + offsetY;
}
int toCrdX(double x)
{
	return (x - offsetX) * scale + sW / 2;
}
int toCrdY(double y)
{
	return -(y - offsetY) * scale + sH / 2;
}

void line(RenderWindow& window, int x1, int y1, int x2, int y2, Color color)
{
	Vertex line[] = { Vertex(Vector2f(x1, y1), color), Vertex(Vector2f(x2, y2), color) };
	window.draw(line, 2, Lines);
}

void putPixel(RenderWindow& window, int cX, int cY, Color color)
{
	line(window, cX, cY, cX + 1, cY + 1, color);
}

void bridge(RenderWindow& window, const FuncYX& func, double xM1, double xM2)
{
	double yM1, yM2;
	if (!func.consider(yM1, xM1) || !func.consider(yM2, xM2))
		return;
	int xC1 = toCrdX(xM1);
	int xC2 = toCrdX(xM2);
	int yC1 = toCrdY(yM1);
	int yC2 = toCrdY(yM2);
	if (!onScreen(xC1, yC1) && !onScreen(xC2, yC2))
		return;
	putPixel(window, xC1, yC1, colorGraph);
	putPixel(window, xC2, yC2, colorGraph);
	if (abs(yC1 - yC2) > 1)
	{
		double xMid = xM1 + (xM2 - xM1) / 2;
		bridge(window, func, xM1, xMid);
		bridge(window, func, xMid, xM2);
	}
}

void construct(RenderWindow& window, const FuncYX& func)
{
	for (int i = 0; i < sW - 1; i++)
	{
		int xC1 = i;
		int xC2 = i + 1;
		double xM1 = toMathX(xC1);
		double xM2 = toMathX(xC2);
		bridge(window, func, xM1, xM2);
	}
}

//void construct(RenderWindow& window, const FuncYX& func)
//{
//	bool first = 1;
//	int prevX, prevY;
//	for (double x = 0; x < sW; x += constructStep)
//	{
//		int cX = x, cY;
//		double mX, mY;
//		mX = toMathX(x);
//		if (!func.consider(mY, mX))
//		{
//			first = 1;
//			continue;
//		}
//		cY = toCrdY(mY);
//		if (!first && (onScreen(prevX, prevY) || onScreen(cX, cY)))
//			line(window, prevX, prevY, cX, cY, colorGraph);
//		first = 0;
//		prevX = cX;
//		prevY = cY;
//	}
//}

int main()
{
	fin.open("input.txt");
	fout.open("output.txt");
	fout.precision(4);
	initColors();
	initOperations();

	string str;
	fin >> str;
	FuncYX func = FuncYX(Expression(str));

	RenderWindow window(VideoMode(sW, sH), "Graph_XY");
	bool changed = 1;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
				changed = 1;
			if (event.type == Event::Closed)
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::W))
			offsetY++;
		if (Keyboard::isKeyPressed(Keyboard::S))
			offsetY--;
		if (Keyboard::isKeyPressed(Keyboard::A))
			offsetX--;
		if (Keyboard::isKeyPressed(Keyboard::D))
			offsetX++;
		if (Keyboard::isKeyPressed(Keyboard::Up))
			scale--;
		if (Keyboard::isKeyPressed(Keyboard::Down))
			scale++;
		if (changed)
		{
			cout.precision(2);
			cout << fixed << scale << space << offsetX << space << offsetY << endl;
			window.clear();
			construct(window, func);
			window.display();
			changed = 0;
		}
	}

	return 0;
}