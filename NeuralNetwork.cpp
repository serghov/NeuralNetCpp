#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(vector<int> shape, mathFunction* activation, mathFunction* outputActivation, mathFunction* regularization, vector<string> inputNames)
{
	this->network = vector<vector<Neuron> >(shape.size());

	int k = 0;

	for (int i = 0; i < shape.size(); i++)
	{
		this->network[i] = vector<Neuron>(shape[i]);
		for (int j = 0; j < this->network[i].size(); j++)
		{
			string name;
			if (i == 0)
				name = inputNames[j];
			else
				name = std::to_string(k++);

			if (i == shape.size() - 1)			
				this->network[i][j] = Neuron(name, outputActivation);
			else
				this->network[i][j] = Neuron(name, activation);

			if (i)
			{
				for (int g = 0; g < this->network[i - 1].size(); g++)
				{
					NeuralLink *link = new NeuralLink(&this->network[i - 1][g], &this->network[i][j], regularization);
					this->network[i - 1][g].outputs.push_back(link);
					this->network[i][j].inputs.push_back(link);
				}
			}
		}
	}
}


double NeuralNetwork::forwardProp(vector<double> &inputs)
{
	int i, j;

	for (i = 0; i < this->network[0].size(); i++)
		this->network[0][i].output = inputs[i];

	for (i = 1; i < this->network.size(); i++)
	{
		for (int j = 0; j < this->network[i].size(); j++)
		{
			this->network[i][j].update();
		}
	}
	
	return this->network[this->network.size() - 1][0].output;
}

void NeuralNetwork::backwardProp(double target, mathFunction* errorFunction)
{
	int i, j;
	this->network[this->network.size() - 1][0].outputDer = errorFunction->dfdx(this->network[this->network.size() - 1][0].output, target);

	for (i = this->network.size() - 1; i > 0; i--)
	{
		for (j = 0; j < this->network[i].size(); j++)
		{
			this->network[i][j].inputDer = this->network[i][j].outputDer * this->network[i][j].activation->dfdx(this->network[i][j].totalInput);
			this->network[i][j].accInputDer += this->network[i][j].inputDer;
			this->network[i][j].numAccInputDer++;
		}

		for (j = 0; j < this->network[i].size(); j++)
		{
			Neuron* neuron = &this->network[i][j];
			for (int g = 0; g < neuron->inputs.size(); g++)
			{
				neuron->inputs[g]->errorDer = neuron->inputDer * neuron->inputs[g]->source->output;
				neuron->inputs[g]->accErrorDer += neuron->inputs[g]->errorDer;
				neuron->inputs[g]->numAccError++;
			}
		}
		if (i == 1)
			continue;

		for (j = 0; j < this->network[i - 1].size(); j++)
		{
			Neuron *neuron = &this->network[i - 1][j];
			neuron->outputDer = 0;
			for (int g = 0; g < neuron->outputs.size(); g++)
			{
				neuron->outputDer += neuron->outputs[g]->weight * neuron->outputs[g]->dest->inputDer;
			}
		}
	}

}