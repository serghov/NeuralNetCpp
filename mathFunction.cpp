#include "mathFunction.h"

double mathFunction::f(double x)
{
	return x;
}

double mathFunction::dfdx(double x)
{
	return 1;
}

double mathFunction::f(double x, double y)
{
	return x;
}

double mathFunction::dfdx(double x, double y)
{
	return 1;
}

double mathFunction::f(int target, int current, double x)
{
	return x;
}

double mathFunction::dfdx(int target, int current, double x)
{
	return 1;
}

vector<double> mathFunction::f(vector<double> &x)
{
	return x;
}

vector<double> mathFunction::dfdx(vector<double> &x)
{
	return vector<double>(x.size());
}

