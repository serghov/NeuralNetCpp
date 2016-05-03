#include "NeuralLink.h"


NeuralLink::NeuralLink(Neuron* source, Neuron* dest, mathFunction* regularization)
{
	this->name = source->name + " - " + dest->name;
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(-0.5, 0.5);//change this to depend on network, argument maybe, also make static random this is slow!!!

	this->weight = dis(gen);
	this->weight = 0.1;//remove
	this->source = source;
	this->dest = dest;
	this->regularization = regularization;
}