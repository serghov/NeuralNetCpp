#pragma once
#include "mathFunction.h"

class squareError : public mathFunction {
public:
	virtual double f(double x, double y);
	virtual double dfdx(double x, double y);
};