#pragma once
#include "Neuron.h"
#include "NeuralLink.h"

namespace nncpp {
	class NeuralLayer {
	public:
		bool isSoftmax;
		mathFunction *regularization;
		vector<Neuron> neurons;
		mathFunction *activation;
		NeuralLayer();
		NeuralLayer(const NeuralLayer &b);
		NeuralLayer(int size, mathFunction *activation, mathFunction *regularization, bool isSoftmax);
		void update();
		int size();
		Neuron& operator[](int i);
		vector<double> toVector();
		string toString();
		void updateWeights(double learningRate, double regularizationRate);
		void link(NeuralLayer& prev);
		NeuralLayer* clone() const;
	};
}

