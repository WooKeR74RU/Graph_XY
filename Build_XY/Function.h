#pragma once
#include "Utilities.h"
#include "Expression.h"

class Function
{
private:
	Expression expr;
public:
	string argument;
	Function();
	Function(const Expression& expr, const string& argument);
	void setArgument(double value);
	bool consider(double& res) const;
};