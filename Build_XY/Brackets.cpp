#pragma once
#include "Brackets.h"

string handleUnaryMinus(const string& expr)
{
	string res(expr);
	int en = res.size() - 1;
	int bal = 0;
	for (int i = expr.size() - 1; 0 <= i; i--)
	{
		if (res[i] == '(')
			bal--;
		if (res[i] == ')')
			bal++;
		if (bal || res[i] == '(' || res[i] == ')')
			continue;
		if (isOperationsSymbol(res[i]))
		{
			if (res[i] == '-')
			{
				if (!isNumber(res[i - 1]) && res[i - 1] != 'x')
				{
					res.insert(i, "(0");
					res.insert(en + 3, ")");
				}
			}
			else
			{
				en = i - 1;
			}
		}
	}
	return res;
}

string buildBracketsInternalExpr(const string& expr)
{
	string res(expr);
	int st;
	int bal = 0;
	for (int i = 0; i < res.size(); i++)
	{
		if (res[i] == '(')
		{
			if (!bal)
				st = i;
			bal++;
		}
		if (res[i] == ')')
		{
			bal--;
			if (!bal)
			{
				int en = i;
				string inter = buildBracketsExpr(substr(res, st + 1, en - 1));
				if (inter[0] == '(' && inter[inter.size() - 1] == ')')
				{
					inter.erase(inter.begin());
					inter.pop_back();
				}
				erase(res, st + 1, en - 1);
				res.insert(st + 1, inter);
				i = st + inter.size() + 1;
			}
		}
	}
	return res;
}

string buildBracketsExpr(const string& expr)
{
	string res(expr);
	res = handleUnaryMinus(res);
	res = buildBracketsInternalExpr(res);
	int prior = 0;
	int operPos = 0;
	int bal = 0;
	for (int i = res.size() - 1; 0 <= i; i--)
	{
		if (res[i] == '(')
			bal++;
		if (res[i] == ')')
			bal--;
		if (bal || res[i] == '(' || res[i] == ')')
			continue;
		if (res[i] == '+' || res[i] == '-')
		{
			operPos = i;
			prior = 1;
			break;
		}
		if (res[i] == '*' || res[i] == '/')
		{
			if (!prior || prior == 3)
			{
				operPos = i;
				prior = 2;
			}
		}
		if (res[i] == '^')
		{
			if (!prior)
			{
				operPos = i;
				prior = 3;
			}
		}
	}
	if (!operPos)
		return res;
	string first = buildBracketsExpr(substr(res, 0, operPos - 1));
	string second = buildBracketsExpr(substr(res, operPos + 1, res.size() - 1));
	return '(' + first + res[operPos] + second + ')';
}