#pragma once
#include <string>
#include <cmath>
#include <vector>
using namespace std;

class mathFunction {
public:
	string name;
	virtual double f(double x);
	virtual double dfdx(double x);

	virtual double f(double x, double y);
	virtual double dfdx(double x, double y);

	virtual double f(int target, int current, double x);
	virtual double dfdx(int target, int current, double x);

	virtual vector<double> f(vector<double> &x);
	virtual vector<double> dfdx(vector<double> &x);

};