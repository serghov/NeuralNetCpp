#include <iostream>
#include "NeuralNetwork.h"

#include <vector>
#include <iomanip>

using namespace std;

int main()
{
	vector<int> shape(2);
	shape[0] = 1;
	shape[1] = 20;



	vector<string> inputNames(1);
	inputNames[0] = "uxt";
	//inputNames[1] = "dzi";

	

	NeuralNetwork myNet(shape,new sigmoid,new sigmoid,new L1, inputNames);//make static vars for math functions

	vector<double> input(1);
	input[0] = 20;
	cout << fixed << setprecision(5);

	for (int i = 0; i < 100; i++)
	{
		myNet.forwardProp(input);
		myNet.backwardProp(0.3, new squareError);


		cout << "output \t" << myNet.network[1][0].output << endl;
		cout << "deriv \t" << myNet.network[myNet.network.size() - 1][0].outputDer << endl;

		cout << "weight \t" << myNet.network[1][0].inputs[0]->weight << endl;
		cout << "bias \t" << myNet.network[1][0].bias << endl;

		cout << "weights" << endl;

		for (int j = 0; j < myNet.network[0][0].outputs.size(); j++)		
			cout << myNet.network[0][0].outputs[j]->weight << " ";
		
		cout << endl;
		
		cout << "------------" << endl;

		myNet.updateWeights(0.1, 0);
		
	}
	
	squareError *tmp = new squareError;

	int t;
	cin >> t;
	

	return 0;
}