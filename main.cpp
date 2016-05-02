#include <iostream>
#include "NeuralNetwork.h"

#include <vector>

using namespace std;

int main()
{
	vector<int> shape(2);
	shape[0] = 1;
	shape[1] = 1;

	vector<string> inputNames(1);
	inputNames[0] = "uxt";
	//inputNames[1] = "dzi";

	

	NeuralNetwork myNet(shape,new sigmoid,new sigmoid,new L1, inputNames);//make static vars for math functions

	vector<double> input(1);
	input[0] = 10;

	for (int i = 0; i < 10; i++)
	{
		cout << myNet.forwardProp(input) << endl;
		myNet.backwardProp(10, new squareError);
		myNet.updateWeights(0.1, 0.03);
	}
	
	
	int t;
	cin >> t;
	

	return 0;
}