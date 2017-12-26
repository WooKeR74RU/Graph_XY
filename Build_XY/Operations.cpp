#include "Operations.h"

bool doubleEqual(double a, double b)
{
	return abs(a - b) < eps;
}

bool unaryPlus(double& res, double x)
{
	res = x;
	return 1;
}
bool unaryMinus(double& res, double x)
{
	res = -x;
	return 1;
}
bool abs(double& res, double x)
{
	res = abs(x);
	return 1;
}
bool sqrt(double& res, double x)
{
	if (x > 0 || doubleEqual(x, 0))
	{
		res = sqrt(x);
		return 1;
	}
	return 0;
}
bool log2(double& res, double x)
{
	if (x > 0 || doubleEqual(x, 0))
	{
		res = log2(x);
		return 1;
	}
	return 0;
}
bool sin(double& res, double x)
{
	res = sin(x);
	return 1;
}
bool cos(double& res, double x)
{
	res = cos(x);
	return 1;
}
bool tg(double& res, double x)
{
	if (!doubleEqual(fmod(x + pi / 2, pi), 0))
	{
		res = tan(x);
		return 1;
	}
	return 0;
}
bool ctg(double& res, double x)
{
	if (!doubleEqual(fmod(x, pi), 0))
	{
		res = 1 / tan(x);
		return 1;
	}
	return 0;
}

bool addition(double& res, double a, double b)
{
	res = a + b;
	return 1;
}
bool subtraction(double& res, double a, double b)
{
	res = a - b;
	return 1;
}
bool multiplication(double& res, double a, double b)
{
	res = a * b;
	return 1;
}
bool division(double& res, double a, double b)
{
	if (!doubleEqual(b, 0))
	{
		res = a / b;
		return 1;
	}
	return 0;
}
bool modulo(double& res, double a, double b)
{
	if (!doubleEqual(b, 0))
	{
		res = fmod(a, b);
		return 1;
	}
	return 0;
}
bool exponentiation(double& res, double a, double b)
{
	res = pow(a, b);
	return 1;
}