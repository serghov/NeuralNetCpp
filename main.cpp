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

	

	NeuralNetwork myNet(shape, linear(), linear(), L1(), inputNames);

	vector<double> input(1);
	input[0] = 10;

	cout << myNet.forwardProp(input) << endl;
	myNet.backwardProp(10, squareError());

	for (int i = 0; i < myNet.network.size(); i++)
	{
		for (int j = 0; j < myNet.network[i].size(); j++)
		{
			cout << myNet.network[i][j].outputDer << " ";
		}
		cout << endl;
	}

	int t;
	cin >> t;
	

	return 0;
}