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
		res[i] = myNet.forwardProp(vector<double>{ (i+0.0) / (rangeEnd - rangeStart) / 60.0 + rangeStart});	
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
		cout <<"| "<<(10-i)/10.0 *(rangeEnd - rangeStart) + rangeStart << endl;
	}
	for (i = 0; i < 60; i++)
		cout << "_";
	cout << endl;
}


int main()
{
	vector<int> shape(3);
	shape[0] = 1;
	shape[1] = 20;
	shape[2] = 1;



	vector<string> inputNames(1);
	inputNames[0] = "uxt";

	NeuralNetwork myNet(shape,new sigmoid,new sigmoid,new L1, inputNames);//make static vars for math functions //and a namespace

	cout << fixed << setprecision(5);

	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> rand01(-0.1, 0.1);
	uniform_real_distribution<> rand001(-0.01, 0.01);


	for (int i = 0; i < 10000; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			myNet.forwardProp(vector<double>{0.5 + rand01(gen)});			
			myNet.backwardProp(1, new squareError);
		}
		
		for (int j = 0; j < 50; j++)
		{
			myNet.forwardProp(vector<double>{0 + rand01(gen)});
			myNet.backwardProp(0, new squareError);
		}

		if (i % 1000 == 0)
		{
			cout << "Epoch: " << i << endl;
			plotSingleVarNet(myNet, 0, 1);
			cout << endl << endl;
		}

		myNet.updateWeights(0.1, 0);
		
	}
	
	
	plotSingleVarNet(myNet, 0, 1);


	int t;
	cin >> t;
	

	return 0;
}