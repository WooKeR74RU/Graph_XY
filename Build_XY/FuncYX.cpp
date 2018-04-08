#include "FuncYX.h"

FuncYX::FuncYX()
{ }
FuncYX::FuncYX(const Expression& expr)
{
	this->expr = expr;
}
bool FuncYX::consider(double& res, double x) const
{
	map<string, double> variables;
	variables["x"] = x;
	return expr.consider(res, variables);
}