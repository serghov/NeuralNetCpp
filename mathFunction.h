#pragma once
#include <string>
#include <cmath>

using namespace std;

class mathFunction {
public:
	string name;
	static double f(double x);
	static double dfdx(double x);

	static double f(double x, double y);
	static double dfdx(double x, double y);

	static double dfdn(double x, int n);
};