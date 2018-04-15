#include "Utilities.h"

ifstream& fin()
{
	static ifstream inputFileStream;
	static bool INIT = 0;
	if (!INIT)
	{
		inputFileStream.open("input.txt");
		INIT = 1;
	}
	return inputFileStream;
}
ofstream& fout()
{
	static ofstream outputFileStream;
	static bool INIT = 0;
	if (!INIT)
	{
		outputFileStream.open("output.txt");
		outputFileStream.precision(4);
		INIT = 1;
	}
	return outputFileStream;
}

string substr(const string& str, int l, int r)
{
	return str.substr(l, r - l + 1);
}
string to_string(char c)
{
	return string({ c });
}
string dtos(double val, int precision)
{
	char buffer[20];
	string format = string("%.") + to_string(precision) + string("f");
	sprintf_s(buffer, format.c_str(), val);
	return string(buffer);
}

bool doubleEqual(double a, double b)
{
	return abs(a - b) < eps;
}
double getCloseLowerNum(double num, double val)
{
	int l = -1e9;
	int r = 1e9;
	while (l + 1 < r)
	{
		int mid = l + (r - l) / 2;
		if (num < mid * val)
			r = mid;
		else
			l = mid;
	}
	return val * l;
}

void line(Image& image, int x1, int y1, int x2, int y2, Color color)
{
	int w = abs(x2 - x1);
	int h = abs(y2 - y1);
	bool swapAxes = w < h;
	if (swapAxes)
	{
		swap(x1, y1);
		swap(x2, y2);
	}
	if (x2 < x1)
	{
		swap(x1, x2);
		swap(y1, y2);
	}
	bool isAddY = y1 < y2;
	double k = w ? (double)h / w : 0;
	double curY = y1;
	int y = y1;
	for (int x = x1; x <= x2; x++)
	{
		if (abs(curY - y) > 0.5)
			y += isAddY ? 1 : -1;
		image.setPixel(swapAxes ? y : x, swapAxes ? x : y, color);
		curY += isAddY ? k : -k;
	}
}

void line(RenderWindow& window, int x1, int y1, int x2, int y2, Color color)
{
	Vertex line[] =	{ Vertex(Vector2f(x1, y1), color), Vertex(Vector2f(x2 + 1, y2 + 1), color) };
	window.draw(line, 2, Lines);
}
void setPixel(RenderWindow& window, int x, int y, Color color)
{
	line(window, x, y, x, y, color);
}

void cursorRestriction(const RenderWindow& window)
{
	int w = window.getSize().x;
	int h = window.getSize().y;
	int x = Mouse::getPosition(window).x;
	int y = Mouse::getPosition(window).y;
	int nx = x;
	int ny = y;
	if (nx >= w)
		nx = w;
	if (nx < 0)
		nx = 0;
	if (ny >= h)
		ny = h;
	if (ny < 0)
		ny = 0;
	if (x != nx || y != ny)
		Mouse::setPosition(Vector2i(nx, ny), window);
}
bool isCursorInWindow(const RenderWindow& window)
{
	int w = window.getSize().x;
	int h = window.getSize().y;
	int x = Mouse::getPosition(window).x;
	int y = Mouse::getPosition(window).y;
	return 0 <= x && x < w && 0 <= y && y < h;
}

static array<bool, Keyboard::KeyCount> state;
void keyUp(Keyboard::Key key)
{
	state[key] = 0;
}
bool isKeyDown(Keyboard::Key key)
{
	if (Keyboard::isKeyPressed(key))
	{
		if (!state[key])
		{
			state[key] = 1;
			return 1;
		}
	}
	return 0;
}