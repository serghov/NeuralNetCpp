#pragma once
#include "mathFunction.h"

class tanh : public mathFunction {
public:
	static double f(double x);
	static double dfdx(double x);
};

class relu : public mathFunction {
public:
	static double f(double x);
	static double dfdx(double x);
};

class linear : public mathFunction {
public: 
	static double f(double x);
	static double dfdx(double x);
};

class sigmoid : public mathFunction {
public:
	static double f(double x);
	static double dfdx(double x);
};