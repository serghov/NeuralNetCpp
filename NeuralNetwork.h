#pragma once
#include "mathFunction.h"
#include "Activations.h"
#include "ErrorFunctions.h"
#include "Regularizations.h"

#include "Neuron.h"
#include "NeuralLink.h"

#include <vector>
#include <iostream>
using namespace std;

class NeuralNetwork {
public:
	vector<vector<Neuron> > network;

	NeuralNetwork(vector<int> shape, mathFunction* activation, mathFunction* outputActivation, mathFunction* regularization, vector<string> inputNames);
	double forwardProp(vector<double> &inputs);
	void backwardProp(double target, mathFunction* errorFunction);
};