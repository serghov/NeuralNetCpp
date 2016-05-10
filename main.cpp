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
	vector<int> shape(4);
	shape[0] = 1;
	shape[1] = 5;
	shape[2] = 4;
	shape[3] = 1;
	



	vector<string> inputNames(1);
	inputNames[0] = "uxt";

	NeuralNetwork myNet(shape,new sigmoid,new sigmoid,new L1, inputNames);//make static vars for math functions //and a namespace

	cout << fixed << setprecision(5);

	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> rand01(-0.1, 0.1);
	uniform_real_distribution<> rand001(-0.01, 0.01);

	mathFunction *SQUARE = new squareError;

	for (int i = 0; i < 1500000; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			myNet.forwardProp(vector<double>{j / 50.0});
			myNet.backwardProp(0.5 + 0.5 * cos(j / 50.0 * 3.1415 * 8.0), SQUARE);
		}
		
		if (i % 1000 == 0)
		{
			cout << "Epoch: " << i << endl;
			plotSingleVarNet(myNet, 0, 1);
			cout << endl;
		}
		

		myNet.updateWeights(1, 0);
		
	}
	
	
	plotSingleVarNet(myNet, 0, 1);


	int t;
	cin >> t;
	

	return 0;
}