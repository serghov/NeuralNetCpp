#pragma once
#include "Neuron.h"
#include "NeuralLink.h"

namespace nncpp {
	class NeuralLayer {
	public:
		bool isSoftmax;
		vector<Neuron> neurons;
		mathFunction *activation;
		NeuralLayer();
		NeuralLayer(int size, mathFunction *activation, bool isSoftmax);
		void update();
		int size();
		Neuron& operator[](int i);
		vector<double> toVector();
	};
}

