#pragma once
#include "mathFunction.h"

class L1 : public mathFunction {
public:
	virtual double f(double x);
	virtual double dfdx(double x);
};

class L2 : public mathFunction {
public:
	virtual double f(double x);
	virtual double dfdx(double x);
};