#include <iostream>
#include "NeuralNetwork.h"

#include <vector>
#include <iomanip>
#include "MNIST.h"
#include <string>
using namespace std;

/*void plotSingleVarNet(NeuralNetwork &myNet, double rangeStart, double rangeEnd)
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
}*/


int main()
{

	MNIST mnist("C:\\Users\\levonstepan\\Documents\\Visual Studio 2013\\Projects\\NeuralNetCpp-master\\x64\\Release\\train.csv", 42000);
	cout <<"data size "<< mnist.images[0].size() << endl;
	vector<int> shape(3);
	shape[0] = 784;
	shape[1] = 70;
	shape[2] = 10;



	vector<string> inputNames(784);
	for (int i = 0; i < inputNames.size(); i++)
		inputNames[0] = "uxt " + std::to_string(i);

	NeuralNetwork myNet(shape,new sigmoid,new sigmoid,new L1, inputNames);//make static vars for math functions //and a namespace

	cout << fixed << setprecision(5);

	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> rand01(-0.1, 0.1);
	uniform_real_distribution<> rand001(-0.01, 0.01);

	

	for (int i = 0; i < 10000; i++)
	{
		for (int j = 0; j < 500; j++)
		{
			myNet.forwardProp(mnist.images[j]);			
			myNet.backwardProp(mnist.labels[j], new squareError);
			myNet.updateWeights(0.1, 0);
		}
		int loss=0;
		for (int j = 0; j < 500; j++)
		{
			vector<double> res = myNet.forwardProp(mnist.images[j]);
			int maxNum = 0;
			for (int g = 0; g < 10; g++)
			{
				if (res[g]>res[maxNum])
					maxNum = g;
				cout << res[g] << " ";
			}
			cout << endl;

			if (maxNum == mnist.labels[j])
				loss++;

		}
		cout << "current loss: "<<1.0 - loss/500.0 << endl;

		if (i % 1000 == 0)
		{
			cout << "Epoch: " << i << endl;
			//plotSingleVarNet(myNet, 0, 1);
			cout << endl << endl;
		}

		myNet.updateWeights(0.1, 0);
		
	}
	
	
	//plotSingleVarNet(myNet, 0, 1);


	int t;
	cin >> t;
	

	return 0;
}