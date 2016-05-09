#include "Regularizations.h"

double L1::f(double x)
{
	return abs(x);
}

double L1::dfdx(double x)
{
	if (x > 0)
		return 1;
	return -1;
}

double L2::f(double x)
{
	return 0.5*x*x;
}

double L2::dfdx(double x)
{
	return x;
}