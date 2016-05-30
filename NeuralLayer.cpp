#include "NeuralLayer.h"

namespace nncpp {
	NeuralLayer::NeuralLayer() {

	}

	NeuralLayer::NeuralLayer(int size, mathFunction *activation, mathFunction *regularization, bool isSoftmax)
	{
		this->neurons = vector<Neuron>(size);
		this->activation = activation;
		for (int i = 0; i < this->neurons.size(); i++)
		{
			this->neurons[i] = Neuron(std::to_string(i), activation);
		}
		this->isSoftmax = isSoftmax;
		this->regularization = regularization;
	}

	void NeuralLayer::update()
	{
		int i;
		if (this->isSoftmax)
		{
			double sum = 0;
			for (i = 0; i < this->size(); i++)
				sum += exp(this->neurons[i].update());
			for (i = 0; i < this->size(); i++)
				this->neurons[i].output = exp(this->neurons[i].totalInput) / sum;
		}
		else
		{
			for (i = 0; i < this->neurons.size(); i++)			
				this->neurons[i].output = this->activation->f(this->neurons[i].update());
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

	vector<double> NeuralLayer::toVector()
	{
		vector<double> res(this->size());
		for (int i = 0; i < this->size(); i++)
			res[i] = this->neurons[i].output;
		return res;
	}

	string NeuralLayer::toString()
	{
		string res = "";
		res += std::to_string(this->size()) + "\n";
		for (int i = 0; i < this->size(); i++)
		{
			res += this->neurons[i].toString();
		}
		return res;
	}

	void NeuralLayer::updateWeights(double learningRate, double regularizationRate)
	{
		for (int i = 0; i < this->size(); i++)
			this->neurons[i].updateWeights(learningRate, regularizationRate);
	}

	void NeuralLayer::link(NeuralLayer &prev)
	{
		int i, j;
		for (i = 0; i < prev.size(); i++)
		{
			for (j = 0; j < this->size(); j++)
			{
				NeuralLink *link = new NeuralLink(&prev[i], &this->neurons[j], this->regularization);
				prev[i].outputs.push_back(link);
				this->neurons[j].inputs.push_back(link);
			}
		}
	}
}