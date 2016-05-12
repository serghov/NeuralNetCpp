#pragma once
#include "mathFunction.h"

namespace nncpp {
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

	class Regularizations {
	public:
		static mathFunction* L1;
		static mathFunction* L2;
	};
}

