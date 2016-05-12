#include "ErrorFunctions.h"

namespace nncpp {

	mathFunction* ErrorFunctions::SQUARE = new squareError();

	double squareError::f(double x, double y)
	{
		return 0.5 * (y - x)*(y - x);
	}

	double squareError::dfdx(double x, double y)
	{
		return x - y;
	}

	double logMin::f(int target, int current, double x)
	{
		//TODO
	}

	double logMin::dfdx(int target, int current, double x)
	{
		if (target == current)
			return -1.0 / x;
		return 0;
	}
}

