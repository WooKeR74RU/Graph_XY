#pragma once
#include "Utilities.h"

namespace Operations
{
	bool Abs(double& res, double a);
	bool Sqrt(double& res, double a);
	bool Log2(double& res, double a);
	bool Sin(double& res, double a);
	bool Cos(double& res, double a);

	bool Sum(double& res, double a, double b);
	bool Difference(double& res, double a, double b);
	bool Multiplication(double& res, double a, double b);
	bool Division(double& res, double a, double b);
	bool Exponentiation(double& res, double a, double b);
}