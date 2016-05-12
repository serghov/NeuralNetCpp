#pragma once
#include "mathFunction.h"
#include "Activations.h"
#include "ErrorFunctions.h"
#include "Regularizations.h"

#include "Neuron.h"
#include "NeuralLink.h"

#include "NeuralLayer.h"
#include <vector>
#include <iostream>
using namespace std;

namespace nncpp {
	class NeuralNetwork {
	public:
		vector<NeuralLayer> network;

		NeuralNetwork(vector<int> shape, mathFunction* activation, mathFunction* outputActivation, mathFunction* regularization, vector<string> inputNames);
		double forwardProp(vector<double> &inputs);
		void backwardProp(double target, mathFunction* errorFunction);
		void updateWeights(double learningRate, double regularizationNumber);
	};
}