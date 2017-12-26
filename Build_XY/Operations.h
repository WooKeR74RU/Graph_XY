#pragma once
#include "Operations.h"
#include "Utilities.h"

const double pi = 3.14159265358979323846;
const double eps = 1e-9;

bool doubleEqual(double a, double b);

bool unaryPlus(double& res, double x);
bool unaryMinus(double& res, double x);
bool abs(double& res, double x);
bool sqrt(double& res, double x);
bool log2(double& res, double x);
bool sin(double& res, double x);
bool cos(double& res, double x);
bool tg(double& res, double x);
bool ctg(double& res, double x);

bool addition(double& res, double a, double b);
bool subtraction(double& res, double a, double b);
bool multiplication(double& res, double a, double b);
bool division(double& res, double a, double b);
bool modulo(double& res, double a, double b);
bool exponentiation(double& res, double a, double b);