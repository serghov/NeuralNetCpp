#include "Neuron.h"

namespace nncpp {
	Neuron::Neuron()
	{
		this->name = "noname";
	}

	Neuron::Neuron(string name, mathFunction* activation)
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
		//this->output = this->activation->f(this->totalInput);
		return this->totalInput;
	}

	string Neuron::toString()
	{
		string res = "";
		res += std::to_string(this->bias) + "\n";
		for (int i = 0; i < this->inputs.size(); i++)
			res += std::to_string(this->inputs[i]->weight) + " ";
		res += "\n";
		return res;
	}

	void Neuron::updateWeights(double learningRate, double regularizationRate)
	{
		this->bias -= learningRate * this->accInputDer / (this->numAccInputDer + 0.0);
		this->accInputDer = 0;
		this->numAccInputDer = 0;

		for (int i = 0; i < this->inputs.size(); i++)
		{
			NeuralLink *neuralLink = this->inputs[i];
			double regulDer = neuralLink->regularization->dfdx(neuralLink->weight);
			if (neuralLink->numAccError > 0)
			{
				neuralLink->weight -= learningRate * (neuralLink->accErrorDer + regularizationRate * regulDer) / (neuralLink->numAccError + 0.0);
				neuralLink->accErrorDer = 0;
				neuralLink->numAccError = 0;
			}
		}
	}

}

