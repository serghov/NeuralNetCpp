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

		NeuralNetwork(vector<int> shape, mathFunction* activation, mathFunction* outputActivation, mathFunction* regularization, bool isSoftmax);// change the constructor to layer per layer type at some point
		vector<double> forwardProp(vector<double> &inputs);
		void backwardProp(double target, mathFunction* errorFunction);
		void updateWeights(double learningRate, double regularizationNumber);
		double getAverageError(vector<double> input, double target, mathFunction *errorFunction);

		void doAnnealingStep(vector<vector<double> > &inputs, vector<int> &labels, int size, double T);
		string toString();
	};
}