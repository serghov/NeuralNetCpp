#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "NeuralNetwork.h"

#include <vector>
#include <iomanip>

#include <cv.h>
#include <highgui.h>


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

void net2Mat(NeuralNetwork &myNet, cv::Mat &mat)
{
	int x, y;
	for (int x = 0; x < mat.cols; x++)
	{
		for (int y = 0; y < mat.rows; y++)
		{
			int tmp = 255 * myNet.forwardProp(vector<double>{x / (mat.cols / 0.5) - 1.0, y / (mat.rows / 0.5) - 1.0});
			cv::circle(mat, cv::Point(x, y), 1, cv::Scalar(tmp, tmp, tmp));
		}
	}
}

int main()
{
	vector<int> shape(7);
	shape[0] = 2;
	shape[1] = 30;	
	shape[2] = 10;
	shape[3] = 10;
	shape[4] = 10;
	shape[5] = 10;
	shape[6] = 1;

	
	cv::Mat inputImage = cv::imread("D:\\skhachat.png");
	cv::Mat outputImage = inputImage.clone();

	vector<string> inputNames(2);
	inputNames[0] = "x";
	inputNames[1] = "y";

	NeuralNetwork myNet(shape,new relu,new relu,new L1, inputNames);//make static vars for math functions //and a namespace

	cout << fixed << setprecision(5);

	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> rand01(-0.1, 0.1);
	uniform_real_distribution<> rand001(-0.01, 0.01);

	mathFunction *SQUARE = new squareError;

	for (int i = 0; i < 100000000; i++)
	{
		
		for (int x = 0; x < inputImage.cols; x++)
		{
			for (int y = 0; y < inputImage.rows; y++)
			{
				if (rand01(gen) < 0.09)
					continue;
				myNet.forwardProp(vector<double>{x / (inputImage.cols / 0.5) - 1.0, y / (inputImage.rows / 0.5) - 1.0});
				myNet.backwardProp(inputImage.at<cv::Vec3b>(cv::Point(x, y))[0] / 255.0, SQUARE);
			}
		}

		if (i % 100 == 0)
		{
			cout << "Epoch: " << i << endl;
			//plotSingleVarNet(myNet, 0, 1);
			//cout << endl;
			net2Mat(myNet, outputImage);
			cv::imwrite("D:\\stuff.png", outputImage);

		}
		
		
		//cv::imshow("output", outputImage);
		if (i<10000)
			myNet.updateWeights(0.01, 0);
		else
			myNet.updateWeights(0.01 * (10000 / (i+0.0)), 0);



		
		
	}

	
	//plotSingleVarNet(myNet, 0, 1);


	int t;
	cin >> t;
	

	return 0;
}
