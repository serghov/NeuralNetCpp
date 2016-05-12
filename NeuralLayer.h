#pragma once
#include "Neuron.h"
#include "NeuralLink.h"

namespace nncpp {
	class NeuralLayer {
	public:
		vector<Neuron> neurons;
		mathFunction *activation;
		NeuralLayer();
		NeuralLayer(int size, mathFunction *activation);
		void update();
		int size();
		Neuron& operator[](int i);
	};
}

