#include "ExpressionTree.h"

void initOperations()
{
	singleFuncs["abs"] = &Operations::Abs;
	singleFuncs["sqrt"] = &Operations::Sqrt;
	singleFuncs["log"] = &Operations::Log2;
	singleFuncs["sin"] = &Operations::Sin;
	singleFuncs["cos"] = &Operations::Cos;
	doubleFuncs['+'] = &Operations::Sum;
	doubleFuncs['-'] = &Operations::Difference;
	doubleFuncs['*'] = &Operations::Multiplication;
	doubleFuncs['/'] = &Operations::Division;
	doubleFuncs['^'] = &Operations::Exponentiation;
}

Node::Node(double val)
{
	type = 0;
	value = val;
}
Node::Node()
{
	type = 1;
}
Node::Node(singleMathFunc func, Ptr val)
{
	type = 2;
	singleFunc = func;
	firstVal = val;
}
Node::Node(doubleMathFunc func, Ptr first, Ptr second)
{
	type = 3;
	doubleFunc = func;
	firstVal = first;
	secondVal = second;
}

bool Node::consider(double& res, double x) const
{
	if (type == 0)
	{
		res = value;
		return 1;
	}
	if (type == 1)
	{
		res = x;
		return 1;
	}
	if (type == 2)
	{
		double val;
		if (!firstVal->consider(val, x))
			return 0;
		return singleFunc(res, val);
	}
	if (type == 3)
	{
		double first, second;
		if (!firstVal->consider(first, x))
			return 0;
		if (!secondVal->consider(second, x))
			return 0;
		return doubleFunc(res, first, second);
	}
}

Function::Function(const Node::Ptr& expressionTreeRoot)
{
	this->expressionTreeRoot = expressionTreeRoot;
}
Function::Function(const string& expr)
{
	*this = Function(buildExpressionTree(expr));
}
bool Function::consider(double& res, double x) const
{
	return expressionTreeRoot->consider(res, x);
}

Node::Ptr buildExpressionTree(const string& expr)
{
	if (expr[0] != '(')
	{
		if (expr[0] == 'x')
			return new Node();
		if (isLetter(expr[0]))
		{
			int brackPos;
			for (int i = 0; i < expr.size(); i++)
			{
				if (expr[i] == '(')
				{
					brackPos = i;
					break;
				}
			}
			string funcName = substr(expr, 0, brackPos - 1);
			string inner = substr(expr, brackPos + 1, expr.size() - 2);
			return new Node(singleFuncs[funcName], buildExpressionTree(inner));
		}
		return new Node(stod(expr));
	}
	int operPos;
	int bal = 0;
	for (int i = 1; i < expr.size(); i++)
	{
		if (expr[i] == '(')
			bal++;
		if (expr[i] == ')')
			bal--;
		if (!bal)
		{
			if (isOperationsSymbol(expr[i]))
			{
				operPos = i;
				break;
			}
		}
	}
	string first = substr(expr, 1, operPos - 1);
	string second = substr(expr, operPos + 1, expr.size() - 2);
	return new Node(doubleFuncs[expr[operPos]], buildExpressionTree(first), buildExpressionTree(second));
}