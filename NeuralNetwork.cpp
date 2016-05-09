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


vector<double> NeuralNetwork::forwardProp(vector<double> &inputs)
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

	double softmaxSum = 0;

	for (i = 0; i < this->network[this->network.size() - 1].size(); i++)
	{
		Neuron *neuron = &this->network[this->network.size() - 1][i];
		softmaxSum += exp(neuron->totalInput);
	}

	for (i = 0; i < this->network[this->network.size() - 1].size(); i++)
	{
		Neuron *neuron = &this->network[this->network.size() - 1][i];
		neuron->output = exp(neuron->totalInput) / softmaxSum;
	}


	//return this->network[this->network.size() - 1][0].output;
	return NeuralNetwork::layer2vector(this->network[this->network.size() - 1]);
}

vector<double> NeuralNetwork::layer2vector(vector<Neuron> &layer)
{
	vector<double> res(layer.size());
	for (int i = 0; i < layer.size(); i++)
		res[i] = layer[i];
	return res;
}

void NeuralNetwork::backwardProp(double target, mathFunction* errorFunction)
{
	int i, j;
	//this->network[this->network.size() - 1][0].outputDer = errorFunction->dfdx(this->network[this->network.size() - 1][0].output, target);

	for (i = 0; i<this->network[this->network.size() - 1].size(); i++)
	{
		Neuron *neuron = &this->network[this->network.size() - 1][i];
		neuron->outputDer = 0;
		if (i == (int)target)
			neuron->outputDer = -1.0 / neuron->output;
	}


	for (i = this->network.size() - 1; i > 0; i--)
	{
		for (j = 0; j < this->network[i].size(); j++)
		{
			Neuron* neuron = &this->network[i][j];

			neuron->inputDer = neuron->outputDer * neuron->activation->dfdx(neuron->totalInput);
			neuron->accInputDer += neuron->inputDer;
			neuron->numAccInputDer++;
		}

		for (j = 0; j < this->network[i].size(); j++)
		{
			Neuron* neuron = &this->network[i][j];
			for (int g = 0; g < neuron->inputs.size(); g++)
			{
				NeuralLink *neuralLink = neuron->inputs[g];
				neuralLink->errorDer = neuron->inputDer * neuralLink->source->output;
				neuralLink->accErrorDer += neuralLink->errorDer;
				neuralLink->numAccError++;
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

void NeuralNetwork::updateWeights(double learningRate, double regularizationRate)
{
	for (int i = 1; i < this->network.size(); i++)
	{
		for (int j = 0; j < this->network[i].size(); j++)
		{
			Neuron* neuron = &this->network[i][j];
			if (neuron->numAccInputDer > 0)
			{
				neuron->bias -= learningRate * neuron->accInputDer / (neuron->numAccInputDer + 0.0);
				neuron->accInputDer = 0;
				neuron->numAccInputDer = 0;
			}

			for (int g = 0; g < neuron->inputs.size(); g++)
			{
				NeuralLink *neuralLink = neuron->inputs[g];
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
}