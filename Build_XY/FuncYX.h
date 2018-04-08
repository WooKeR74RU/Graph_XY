#pragma once
#include "Utilities.h"
#include "Expression.h"

class FuncYX
{
private:
	Expression expr = Expression(string());
public:
	FuncYX();
	FuncYX(const Expression& expr);
	bool consider(double& res, double x) const;
};