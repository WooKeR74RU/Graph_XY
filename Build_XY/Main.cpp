#include "Utilities.h"
#include "Expression.h"

int main()
{
	fin.open("input.txt");
	fout.open("output.txt");
	fout.precision(4);

	string str;
	fin >> str;

	initOperations();
	Expression expr(str);
	double res;
	map<string, double> variables;
	variables["x"] = 2;
	variables["y"] = 3;

	if (!expr.consider(res, variables))
		fout << "Undefined";
	else
		fout << fixed << res;

	return 0;
}