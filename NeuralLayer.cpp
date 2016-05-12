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
	int i;
	if (this->activation->name == "softmax")
	{
		vector<double> tmp(this->size());
		for (i = 0; i < this->size(); i++)
			tmp[i] = this->neurons[i].update();
		
		vector<double> res = this->activation->f(tmp);
		for (i = 0; i < this->size(); i++)
			this->neurons[i].output = res[i];
	}
	else
	{
		for (i = 0; i < this->neurons.size(); i++)
		{
			this->neurons[i].output = this->activation->f(this->neurons[i].update());
		}
	}//make this better
}

int NeuralLayer::size()
{
	return this->neurons.size();
}

Neuron& NeuralLayer::operator[](int i)
{
	return this->neurons[i];
}