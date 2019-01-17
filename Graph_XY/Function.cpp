#include "Function.h"

Function::Function()
{ }
Function::Function(const Expression& expr, const string& argument)
{
	this->expr = expr;
	this->argument = argument;
}
bool Function::consider(double& res) const
{
	return expr.consider(res);
}
void Function::setArgument(double value)
{
	expr.setVariable(argument, value);
}