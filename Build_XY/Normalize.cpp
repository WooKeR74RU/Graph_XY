#include "Normalize.h"

string normalize(const string& expr)
{
	string res;
	for (int i = 0; i < expr.size(); i++)
	{
		if (expr[i] == ' ')
			continue;
		res.push_back(expr[i]);
	}
	for (int i = 0; i < res.size() - 1; i++)
	{
		char a = res[i];
		char b = res[i + 1];
		if (isLetter(a) && isNumber(b) || isNumber(a) && isLetter(b))
			res.insert(i + 1, "*");
	}
	
	return res;
}