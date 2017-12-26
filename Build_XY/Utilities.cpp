#include "Utilities.h"

string substr(const string& str, int l, int r)
{
	return str.substr(l, r - l + 1);
}

void erase(string& str, int l, int r)
{
	str.erase(l, r - l + 1);
}

bool isLetter(char ch)
{
	return 'a' <= ch && ch <= 'z';
}

bool isNumber(char ch)
{
	return '0' <= ch && ch <= '9';
}

bool isOperationsSymbol(char ch)
{
	return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}