#include "ErrorFunctions.h"

double squareError::f(double x, double y)
{
	return 0.5 * (y - x)*(y - x);
}

double squareError::dfdx(double x, double y)
{
	return x - y;
}