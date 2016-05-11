#include "NeuralLayer.h"

NeuralLayer::NeuralLayer() {

}

NeuralLayer::NeuralLayer(int size, mathFunction *activation)
{
	this->neurons = vector<Neuron>(size);
	this->activation = activation;
	for (int i = 0; i < this->neurons.size(); i++)
	{
		this->neurons[i] = Neuron(std::to_string(i), activation);
	}
}

void NeuralLayer::update()
{
	for (int i = 0; i < this->neurons.size(); i++)
		this->neurons[i].update();
}

int NeuralLayer::size()
{
	return this->neurons.size();
}

Neuron& NeuralLayer::operator[](int i)
{
	return this->neurons[i];
}