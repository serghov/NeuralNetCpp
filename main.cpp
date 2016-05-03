#include <iostream>
#include "NeuralNetwork.h"

#include <vector>
#include <iomanip>

using namespace std;

int main()
{
	vector<int> shape(2);
	shape[0] = 1;
	shape[1] = 1;



	vector<string> inputNames(1);
	inputNames[0] = "uxt";
	//inputNames[1] = "dzi";

	

	NeuralNetwork myNet(shape,new linear,new linear,new L1, inputNames);//make static vars for math functions

	vector<double> input(1);
	input[0] = 0.1;
	cout << fixed << setprecision(5);

	for (int i = 0; i < 10; i++)
	{
		cout << "output \t" << myNet.network[1][0].output << endl;
		cout << "deriv \t" << myNet.network[myNet.network.size() - 1][0].outputDer << endl;

		cout << "weight \t" << myNet.network[1][0].inputs[0]->weight << endl;
		cout << "bias \t" << myNet.network[1][0].bias << endl;

		
		cout << "------------" << endl;

		myNet.forwardProp(input);
		myNet.backwardProp(1, new squareError);

		myNet.updateWeights(0.1, 0);//no idea why
		
	}
	
	squareError *tmp = new squareError;

	int t;
	cin >> t;
	

	return 0;
}