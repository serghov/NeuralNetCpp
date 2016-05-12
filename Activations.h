#pragma once
#include "mathFunction.h"
#include <limits>

namespace nncpp {
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
		string name = "softmax";
		virtual vector<double> f(vector<double> &x);
		virtual vector<double> dfdx(vector<double> &x);
	};

	class Activations {
	public:
		static mathFunction *TANH;// = new Tanh();
		static mathFunction *LINEAR;// = new linear();
		static mathFunction *SIGMOID;// = new sigmoid();
		static mathFunction *RELU;// = new relu();
	};
	
}
 
