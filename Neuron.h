#pragma once
#include "mathFunction.h"
#include "NeuralLink.h"
#include <vector>
#include <string>

using namespace std;

namespace nncpp {
	class NeuralLink;

	class Neuron {
	public:
		string name;
		double bias = 0.1;
		vector<NeuralLink*> inputs, outputs;
		double output = 0, totalInput = 0, outputDer = 0, inputDer = 0;

		double accInputDer = 0; int numAccInputDer = 0;

		mathFunction* activation;
		Neuron();
		Neuron(string name, mathFunction* activation);
		~Neuron();

		double update();

		string toString();
		
	};

}

