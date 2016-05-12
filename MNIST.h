#pragma once
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;


class MNIST {
public:
	vector<vector<double> > images;
	vector<int> labels;

	MNIST(string datafile, int length);
};