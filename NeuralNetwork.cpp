#include "NeuralNetwork.h"

namespace nncpp {
	NeuralNetwork::NeuralNetwork(vector<int> shape, mathFunction* activation, mathFunction* outputActivation, mathFunction* regularization, bool isSoftmax)
	{
		this->network = vector<NeuralLayer>(shape.size());

		int k = 0;

		for (int i = 0; i < shape.size(); i++)
		{
			if (i == shape.size() - 1)
				this->network[i] = NeuralLayer(shape[i], outputActivation, isSoftmax);
			else
				this->network[i] = NeuralLayer(shape[i], activation, false);

			for (int j = 0; j < this->network[i].size(); j++)
			{
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
			this->network[i].update();

		//return this->network[this->network.size() - 1][0].output;
		return this->network[this->network.size() - 1].toVector();
	}

	void NeuralNetwork::backwardProp(double target, mathFunction* errorFunction)
	{
		int i, j;
		for (i = 0; i < this->network[this->network.size() - 1].size(); i++)
		{
			if (this->network[this->network.size() - 1].isSoftmax)
				this->network[this->network.size() - 1][i].outputDer = this->network[this->network.size() - 1][i].output - (double)(i == (int)target);
			else
				this->network[this->network.size() - 1][i].outputDer = errorFunction->dfdx(this->network[this->network.size() - 1][i].output, target);//make the function accept a vector as target
		}


		for (i = this->network.size() - 1; i > 0; i--)
		{
			for (j = 0; j < this->network[i].size(); j++)
			{
				Neuron* neuron = &this->network[i][j];

				if (this->network[this->network.size() - 1].isSoftmax && i == this->network.size() - 1)
					neuron->inputDer = neuron->outputDer;	
				else
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
			this->network[i].updateWeights(learningRate, regularizationRate);
		}
	}

	double NeuralNetwork::getAverageError(vector<double> input, double target, mathFunction *errorFunction)
	{
		return -log(this->forwardProp(input)[(int)target]);//make generic
	}

	void NeuralNetwork::doAnnealingStep(vector<vector<double> > &inputs, vector<int> &labels, int size, double T)
	{
		double curLossVal = 0;
		for (int i = 0; i < size; i++)
			curLossVal += this->getAverageError(inputs[i], 0.0 + labels[i], ErrorFunctions::LOG);
		curLossVal /= size + 0.0;
		random_device rd;
		mt19937 gen(rd());

		uniform_real_distribution<> rand(-0.15, 0.15);
		uniform_real_distribution<> rand01(0, 1);


		vector<double> weights(0);
		for (int i = 0; i < this->network.size(); i++)
		{
			for (int j = 0; j < this->network[i].size(); j++)
			{
				for (int g = 0; g < this->network[i][j].inputs.size(); g++)
				{
					weights.push_back(this->network[i][j].inputs[g]->weight);
					this->network[i][j].inputs[g]->weight += rand(gen);
				}
			}
		}
		vector <double> biases(0);
		for (int i = 0; i < this->network.size(); i++)
		{
			for (int j = 0; j < this->network[i].size(); j++)
			{
				biases.push_back(this->network[i][j].bias);
				this->network[i][j].bias += rand(gen);
			}
		}

		double newLossVal = 0;
		for (int i = 0; i < size; i++)
			newLossVal += this->getAverageError(inputs[i], 0.0 + labels[i], ErrorFunctions::LOG);
		newLossVal /= size + 0.0;

		if (newLossVal < curLossVal)
			return;

		double P = exp((curLossVal - newLossVal) / T);
		double newP = rand01(gen);
		if (P > newP)
			return;
		int k = 0;
		for (int i = 0; i < this->network.size(); i++)
		{
			for (int j = 0; j < this->network[i].size(); j++)
			{
				for (int g = 0; g < this->network[i][j].inputs.size(); g++)
				{
					this->network[i][j].inputs[g]->weight = weights[k++];
				}
			}
		}

		k = 0;
		for (int i = 0; i < this->network.size(); i++)
		{
			for (int j = 0; j < this->network[i].size(); j++)
			{
				this->network[i][j].bias = biases[k++];
			}
		}

	}

	string NeuralNetwork::toString()
	{
		string res = "";
		res += std::to_string(this->network.size()) + "\n";
		for (int i = 0; i < this->network.size(); i++)
			res += this->network[i].toString();
		return res;
	}

}

