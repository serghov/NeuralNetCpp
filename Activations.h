#pragma once
#include "mathFunction.h"
#include <limits>

class Tanh : public mathFunction {
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

class softmax : public mathFunction {
public:
	virtual vector<double> f(vector<double> &x);
	virtual vector<double> dfdx(vector<double> &x);
};
