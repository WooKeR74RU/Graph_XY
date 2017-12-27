#pragma once
#include "Expression.h"
struct FuncYX
{
private:
	Expression expr = Expression(string());
public:
	FuncYX(const Expression& expr);
	bool consider(double& res, double x) const;
};