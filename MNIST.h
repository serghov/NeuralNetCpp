#pragma once
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
using namespace std;


class MNIST {
public:
	vector<vector<double> > images;
	vector<int> labels;

	MNIST();
	MNIST(string datafile, int length);
	void dump(unsigned char *&data, int &size);
	void readFromDump(unsigned char *data, int size);
	void dumpToFile(string location);
	void readDumpFile(string location);
};
