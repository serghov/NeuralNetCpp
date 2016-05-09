#pragma once
#include <string>
#include <cmath>

using namespace std;

class mathFunction {
public:
	string name;
	virtual double f(double x);
	virtual double dfdx(double x);

	virtual double f(double x, double y);
	virtual double dfdx(double x, double y);

};