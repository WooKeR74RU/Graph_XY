#include "Operations.h"

bool Operations::Abs(double& res, double a)
{
	res = abs(a);
	return 1;
}
bool Operations::Sqrt(double& res, double a)
{
	if (a >= 0)
	{
		res = sqrt(a);
		return 1;
	}
	return 0;
}
bool Operations::Log2(double& res, double a)
{
	if (a > 0)
	{
		res = log2(a);
		return 1;
	}
	return 0;
}
bool Operations::Sin(double& res, double a)
{
	res = sin(a);
	return 1;
}
bool Operations::Cos(double& res, double a)
{
	res = cos(a);
	return 1;
}

bool Operations::Sum(double& res, double a, double b)
{
	res = a + b;
	return 1;
}
bool Operations::Difference(double& res, double a, double b)
{
	res = a - b;
	return 1;
}
bool Operations::Multiplication(double& res, double a, double b)
{
	res = a * b;
	return 1;
}
bool Operations::Division(double& res, double a, double b)
{
	if (b != 0)
	{
		res = a / b;
		return 1;
	}
	return 0;
}
bool Operations::Exponentiation(double& res, double a, double b)
{
	res = pow(a, b);
	return 1;
}