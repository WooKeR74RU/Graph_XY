#pragma once
#include <fstream>
#include <cmath> 
#include <vector>
#include <string>
#include <map>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
#define space ' '
#define sqr(x) ((x) * (x))

ifstream& fin();
ofstream& fout();

string substr(const string& str, int l, int r);
string to_string(char c);
string dtos(double val, int precision);

static const double eps = 1e-9;
bool doubleEqual(double a, double b);
double getCloseLowerNum(double num, double val);

void line(Image& image, int x1, int y1, int x2, int y2, Color color);

void line(RenderWindow& window, int x1, int y1, int x2, int y2, Color color);
void setPixel(RenderWindow& window, int x, int y, Color color);

void cursorRestriction(const RenderWindow& window);
bool isCursorInWindow(const RenderWindow& window);