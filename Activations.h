#pragma once
#include "mathFunction.h"

class tanh : public mathFunction {
public:
	virtual double f(double x);
	virtual double dfdx(double x);
};

class relu : public mathFunction {
public:
	virtual double f(double x);
	virtual double dfdx(double x);
};

class linear : public mathFunction {
public: 
	virtual double f(double x);
	virtual double dfdx(double x);
};

class sigmoid : public mathFunction {
public:
	virtual double f(double x);
	virtual double dfdx(double x);
};