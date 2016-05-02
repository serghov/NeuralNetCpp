#include "Neuron.h"

Neuron::Neuron()
{
	this->name = "noname";	
}

Neuron::Neuron(string name, mathFunction activation)
{
	this->name = name;
	this->activation = activation;
}

Neuron::~Neuron()
{
	for (int i = 0; i < inputs.size(); i++)
		delete inputs[i];
	//for (int i = 0; i < outputs.size(); i++)
	//	delete outputs[i];
	//the next one will delete the outputs
}

double Neuron::update()
{
	this->totalInput = this->bias;
	for (int i = 0; i < inputs.size(); i++)
	{
		this->totalInput += inputs[i]->weight * inputs[i]->source->output;
	}
	this->output = this->activation.f(this->totalInput);
	return this->output;
}

