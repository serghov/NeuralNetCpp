#pragma once
#include <string>
#include "Neuron.h"
#include <random>

using namespace std;

class Neuron;

class NeuralLink {
public:
	string name;
	Neuron* source;
	Neuron* dest;

	double weight;//random of some sorts

	double errorDer = 0, accErrorDer = 0; int numAccError = 0;
	mathFunction* regularization;

	NeuralLink(Neuron* source, Neuron* dest, mathFunction* regularization);

};