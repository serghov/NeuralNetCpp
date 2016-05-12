#pragma once
#include "mathFunction.h"

namespace nncpp {

	class squareError : public mathFunction {
	public:
		virtual double f(double x, double y);
		virtual double dfdx(double x, double y);
	};

	class logMin : public mathFunction {
	public:
		string name = "logmin";
		virtual double f(int target, int current, double x);
		virtual double dfdx(int target, int current, double x);
	};

	class ErrorFunctions {
	public:
		static mathFunction* SQUARE;
	};
}

