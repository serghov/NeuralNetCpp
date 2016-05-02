#pragma once
#include "mathFunction.h"

class L1 : public mathFunction {
public:
	static double f(double x);
	static double dfdx(double x);
};

class L2 : public mathFunction {
public:
	static double f(double x);
	static double dfdx(double x);
};