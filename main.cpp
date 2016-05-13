#include <iostream>
#include "NeuralNetwork.h"

#include <vector>
#include <iomanip>

#include "MNIST.h"

using namespace nncpp;

void plotSingleVarNet(NeuralNetwork &myNet, double rangeStart, double rangeEnd)
{
	int i, j;
	vector<double> res(60);
	for (i = 0; i < 60; i++)
	{
		res[i] = myNet.forwardProp(vector<double>{ (i + 0.0) / (rangeEnd - rangeStart) / 60.0 + rangeStart})[0];
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
	MNIST mnist("D:\\Documents\\VisualStudioProjects\\nauralNet\\train.csv", 42000);

	vector<int> shape{ 784, 100 ,10 };

	NeuralNetwork myNet(shape, Activations::SIGMOID, Activations::SIGMOID, Regularizations::L2, true);

	cout << fixed << setprecision(5);

	random_device rd;
	mt19937 gen(rd());

	uniform_real_distribution<> rand001(-0.01, 0.01);
	uniform_real_distribution<> rand01(0, 1);


	double alpha = 0.1;
	//29400 levon, 12600

	int curIterationNum = 0;

	for (int i = 0; i < 1000000; i++)
	{

		for (int j = 0; j < 100; j++)
		{
			myNet.forwardProp(mnist.images[j + curIterationNum * 100]);
			myNet.backwardProp(mnist.labels[j + curIterationNum * 100], ErrorFunctions::SQUARE);
		}

		curIterationNum++;
		curIterationNum %= 294;

		int res = 0;

		if (i % 294 == 0)
		{
			for (int j = 0; j < 12600; j++)
			{
				vector<double> tmp = myNet.forwardProp(mnist.images[j + 29400]);
				int maxi = 0;
				for (int g = 0; g < 10; g++)
				{
					if (tmp[maxi] < tmp[g])
						maxi = g;
				}
				res += maxi == mnist.labels[j + 29400];
			}
			cout << "Epoch: " << i / 294 << endl;
			cout << res / 12600.0 << endl;

			int maxi = 0, mini = 0;
			int maxj = 0, minj = 0;
			for (int j = 0; j < myNet.network[0].size(); j++)
			{
				for (int g = 0; g < myNet.network[0][j].outputs.size(); g++)
				{
					if (myNet.network[0][j].outputs[g]->weight < myNet.network[0][j].outputs[mini]->weight)
					{
						mini = g;
						minj = j;
					}


					if (myNet.network[0][j].outputs[g]->weight > myNet.network[0][j].outputs[mini]->weight)
					{
						maxi = g;
						maxj = j;
					}

				}
			}
			cout << "MIN: " << myNet.network[0][minj].outputs[mini]->weight << endl;
			cout << "MAX: " << myNet.network[0][maxj].outputs[maxi]->weight << endl;

			//alpha /= 2.0;
		}
		//if (i && (i/294)%100 == 0)
		//	alpha /= 2.0;


		myNet.updateWeights(alpha, 0.01);
	}

	plotSingleVarNet(myNet, 0, 1);


	int t;
	cin >> t;

	return 0;
}