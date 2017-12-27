#include "Utilities.h"
#include "FuncYX.h"

//Configuration
const int sW = 800, sH = 600;
const double constructStep = 0.2;
const int findPrecision = 1000;
const int numberPrecision = 3;
const int pointCount = 10000;
const double offsetX = 0;
const double offsetY = 0;
const double k = 80;
const Color colorBackground = Color::Black;
const Color colorAxes = Color::Red;
const Color colorGraph = Color::White;
const Color colorText = Color::Cyan;
const int spaceDistance = 8;
const int markupLength = 4;
const int pointSize = 4;
const int hatchDist = 20;

double rand(double a, double b)
{
	return (b - a) * rand() / RAND_MAX + a;
}

bool onScreen(int cX, int cY)
{
	return 0 <= cX && cX < sW && 0 <= cY && cY < sH;
}
double toMathX(double x)
{
	return (x - sW / 2) / k + offsetX;
}
double toMathY(double y)
{
	return -(y - sH / 2) / k + offsetY;
}
int toCrdX(double x)
{
	return (x - offsetX) * k + sW / 2;
}
int toCrdY(double y)
{
	return -(y - offsetY) * k + sH / 2;
}

void line(RenderWindow& window, int x1, int y1, int x2, int y2)
{
	Vertex line[] = { Vertex(Vector2f(x1, y1)), Vertex(Vector2f(x2, y2)) };
	window.draw(line, 2, Lines);
}

void construct(RenderWindow& window, const FuncYX& func)
{
	bool first = 1;
	int prevX, prevY;
	for (double x = 0; x < sW; x += constructStep)
	{
		int cX = x, cY;
		double mX, mY;
		mX = toMathX(x);
		if (!func.consider(mY, mX))
		{
			first = 1;
			continue;
		}
		cY = toCrdY(mY);
		if (!first && (onScreen(prevX, prevY) || onScreen(cX, cY)))
			line(window, prevX, prevY, cX, cY);
		first = 0;
		prevX = cX;
		prevY = cY;
	}
}

double findIntersectionX(const FuncYX& bot, const FuncYX& top, double l, double r)
{
	for (int i = 0; i < findPrecision; i++)
	{
		double mid = l + (r - l) / 2;
		double resTop, resBot;
		bot.consider(resBot, mid);
		top.consider(resTop, mid);
		if (resBot <= resTop)
			l = mid;
		else
			r = mid;
	}
	return l;
}

int main()
{
	fin.open("input.txt");
	fout.open("output.txt");
	fout.precision(4);

	string str;
	fin >> str;
	initOperations();
	FuncYX func = FuncYX(Expression(str));

	RenderWindow window(VideoMode(sW, sH), "Graph_XY");
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		window.clear();
		construct(window, func);
		window.display();
	}

	return 0;
}