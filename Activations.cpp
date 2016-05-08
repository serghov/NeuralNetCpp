#include "Activations.h"

double Tanh::f(double x)
{
	if (x == std::numeric_limits<double>::max())
		return 1;

	if (x == std::numeric_limits<double>::min())
		return -1;

	double e2x = exp(2.0 * x);
	return (e2x - 1.0) / (e2x + 1.0);
}
double Tanh::dfdx(double x)
{
	double f = Tanh::f(x);
	return 1 - f * f;
}

double relu::f(double x)
{
	if (x < 0)
		return 0;
	return x;
}

double relu::dfdx(double x)
{
	if (x > 0)
		return 1;
	return 0;
}

double linear::f(double x)
{
	return x;
}

double linear::dfdx(double x)
{
	return 1;
}

double sigmoid::f(double x)
{
	return 1.0 / (1.0 + exp(-x));
}

double sigmoid::dfdx(double x)
{
	double f = sigmoid::f(x);
	return f * (1 - f);
}
