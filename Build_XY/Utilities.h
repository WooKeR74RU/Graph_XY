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

ifstream& fin();
ofstream& fout();

string substr(const string& str, int l, int r);
string to_string(char c);

void line(Image& image, int x1, int y1, int x2, int y2, Color color);

void line(RenderWindow& window, int x1, int y1, int x2, int y2, Color color);
void setPixel(RenderWindow& window, int x, int y, Color color);

void cursorRestriction(const RenderWindow& window);