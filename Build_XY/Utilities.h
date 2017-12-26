#pragma once
#define _USE_MATH_DEFINES
#include <fstream>
#include <cmath> 
#include <vector>
#include <string>
#include <map>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
#define endl '\n'
#define space ' '

static ifstream fin;
static ofstream fout;

string substr(const string& str, int l, int r);
string to_string(char c);