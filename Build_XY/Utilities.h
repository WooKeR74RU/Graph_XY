#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;

string substr(const string& str, int l, int r);
void erase(string& str, int l, int r);
bool isLetter(char ch);
bool isNumber(char ch);
bool isOperationsSymbol(char ch);