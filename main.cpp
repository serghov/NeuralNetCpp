#include <iostream>
#include "NeuralNetwork.h"

#include <vector>
#include <iomanip>

#include <fstream>

#include "MNIST.h"

using namespace nncpp;
using namespace std;

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
	MNIST mnist("./train.csv", 42000);

	vector<int> shape{ 784 , 28, 10 };

	NeuralNetwork myNet(shape, Activations::SIGMOID, Activations::SIGMOID, Regularizations::L2, true);

	ofstream fout("network.txt");
	fout << myNet.toString();
	fout.close();

	cout << fixed << setprecision(5);

	random_device rd;
	mt19937 gen(rd());

	uniform_real_distribution<> rand001(-0.01, 0.01);
	uniform_real_distribution<> rand01(0, 1);


	double alpha = 0.1;
	//29400 levon, 12600

	int curIterationNum = 0;

	double lastPercentage = 0;

	vector<vector<double> > trainData(29400);
	vector<int> trainLabels(29400);
	for (int i = 0; i < trainData.size(); i++)
	{
		trainData[i] = mnist.images[i];
		trainLabels[i] = mnist.labels[i];
	}
		
	double T = 10;
	for (int i = 0; i < 200000; i++)
	{
		myNet.doAnnealingStep(trainData, trainLabels, T);\
		if (i%5==0)
			T = 0.7 * T;

		int res = 0;
		double error = 0;
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

			error += myNet.getAverageError(mnist.images[j + 29400], mnist.labels[j + 29400], ErrorFunctions::LOG);
		}
		cout << "Epoch: " << i << endl;
		cout << "Success rate: " << res / 12600.0 << endl;
		cout << "Average error: " << error / 12600.0 << endl;
	}
	return 0;
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
			double error = 0;
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

				error += myNet.getAverageError(mnist.images[j + 29400], mnist.labels[j + 29400], ErrorFunctions::LOG);
			}
			cout << "Epoch: " << i / 294 << endl;
			cout << "Success rate: "<< res / 12600.0 << endl;
			cout << "Average error: "<< error / 12600.0 << endl;


			if (lastPercentage < res / 12600.0)
			{
				ofstream fout("network.txt");
				fout << myNet.toString();
				fout.close();
				lastPercentage = res / 12600.0;
			}
		
		}

		int epoch = i / 294;

		if (epoch > 0 && epoch % 100 == 0)
			alpha *= 0.8;

		myNet.updateWeights(alpha, 0.01);
	}


	int t;
	cin >> t;

	return 0;
}