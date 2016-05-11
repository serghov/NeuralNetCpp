#include <iostream>
#include "NeuralNetwork.h"

#include <vector>
#include <iomanip>



void plotSingleVarNet(NeuralNetwork &myNet, double rangeStart, double rangeEnd)
{
	int i, j;
	vector<double> res(60);
	for (i = 0; i < 60; i++)
	{
		res[i] = myNet.forwardProp(vector<double>{ (i + 0.0) / (rangeEnd - rangeStart) / 60.0 + rangeStart});
	}

	for (i = 0; i < 60; i++)
		cout << "_";
	cout << endl;
	for (i = 0; i < 11; i++)
	{
		for (j = 0; j < 60; j++)
		{
			if ((int)(res[j] * 11) == 10 - i)
				cout << "+";
			else
				cout << " ";
		}
		cout << "| " << (10 - i) / 10.0 *(rangeEnd - rangeStart) + rangeStart << endl;
	}
	for (i = 0; i < 60; i++)
		cout << "_";
	cout << endl;
}


int main()
{
	vector<int> shape(6);
	shape[0] = 1;
	shape[1] = 10;
	shape[2] = 10;
	shape[3] = 10;
	shape[4] = 10;
	shape[5] = 1;


	vector<string> inputNames(1);
	inputNames[0] = "uxt";

	NeuralNetwork myNet(shape, new Tanh, new Tanh, new L1, inputNames);//make static vars for math functions //and a namespace

	cout << fixed << setprecision(5);

	random_device rd;
	mt19937 gen(rd());

	uniform_real_distribution<> rand001(-0.01, 0.01);
	uniform_real_distribution<> rand01(0, 1);


	for (int i = 0; i < 100000; i++)
	{
		//for (int j = 0; j < 50; j++)
		//{
		//	myNet.forwardProp(vector<double>{j/50.0});			
		//	myNet.backwardProp(0.5 + 0.5 * sin(j/50.0 * 3.1415 * 4), new squareError);
		//}
		for (int j = 0; j < 2; j++)
		{
			double k = rand01(gen);
			myNet.forwardProp(vector<double>{k});
			myNet.backwardProp(0.5 + 0.5 * sin(k * 3.1415 * 4), new squareError);
		}

		if (i % 1000 == 0)
		{
			cout << "Epoch: " << i << endl;
			plotSingleVarNet(myNet, 0, 1);
		}
		
		myNet.updateWeights(0.1, 0);
	}

	plotSingleVarNet(myNet, 0, 1);


	int t;
	cin >> t;


	return 0;
}