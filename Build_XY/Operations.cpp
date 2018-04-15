#include "Operations.h"

bool unaryPlus(double& res, double arg)
{
	res = arg;
	return 1;
}
bool unaryMinus(double& res, double arg)
{
	res = -arg;
	return 1;
}
bool abs(double& res, double arg)
{
	res = abs(arg);
	return 1;
}
bool sqrt(double& res, double arg)
{
	if (arg >= 0)
	{
		res = sqrt(arg);
		return 1;
	}
	return 0;
}
bool ln(double& res, double arg)
{
	if (arg > 0)
	{
		res = log(arg);
		return 1;
	}
	return 0;
}
bool lg(double& res, double arg)
{
	if (arg > 0)
	{
		res = log10(arg);
		return 1;
	}
	return 0;
}
bool log(double& res, double arg)
{
	if (arg > 0)
	{
		res = log2(arg);
		return 1;
	}
	return 0;
}
bool sin(double& res, double arg)
{
	res = sin(arg);
	return 1;
}
bool cos(double& res, double arg)
{
	res = cos(arg);
	return 1;
}
bool tg(double& res, double arg)
{
	if (!doubleEqual(fmod(arg + M_PI_2, M_PI), 0))
	{
		res = tan(arg);
		return 1;
	}
	return 0;
}
bool ctg(double& res, double arg)
{
	if (!doubleEqual(fmod(arg, M_PI), 0))
	{
		res = 1 / tan(arg);
		return 1;
	}
	return 0;
}
bool arcsin(double& res, double arg)
{
	if (-1 <= arg && arg <= 1)
	{
		res = asin(arg);
		return 1;
	}
	return 0;
}
bool arccos(double& res, double arg)
{
	if (-1 <= arg && arg <= 1)
	{
		res = acos(arg);
		return 1;
	}
	return 0;
}
bool arctg(double& res, double arg)
{
	res = atan(arg);
	return 1;
}
bool arcctg(double& res, double arg)
{
	res = atan(-arg) + M_PI_2;
	return 1;
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