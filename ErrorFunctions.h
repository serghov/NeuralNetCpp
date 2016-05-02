#pragma once
#include "mathFunction.h"

class squareError : public mathFunction {
public:
	static double f(double x, double y);
	static double dfdx(double x, double y);
};