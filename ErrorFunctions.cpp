#include "ErrorFunctions.h"

namespace nncpp {

	mathFunction* ErrorFunctions::SQUARE = new squareError();
	mathFunction* ErrorFunctions::LOG = new logMin();

	double squareError::f(double x, double y)
	{
		return 0.5 * (y - x)*(y - x);
	}

	double squareError::dfdx(double x, double y)
	{
		return x - y;
	}

	double logMin::f(double x, double y)
	{
		return -log(x - y);
	}

	double logMin::dfdx(double x, double y)
	{
		return y - x;
	}
}

