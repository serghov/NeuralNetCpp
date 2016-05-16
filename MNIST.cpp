#define _CRT_SECURE_NO_WARNINGS

#include "MNIST.h"

MNIST::MNIST()
{

}

MNIST::MNIST(string datafile, int length)
{
	FILE *fin = fopen(datafile.c_str(), "r");
	char c[10000];
	int r = -1;
	labels = vector<int>(length);
	images = vector<vector<double> >(length);

	while (fgets(c, 10000, fin)) {
		if (r == -1) {
			r++;
			continue;
		}
		images[r] = vector<double>(784);
		int col = 0;
		int v = 0;
		for (int i = 0; i < strlen(c); ++i) {
			if (!(c[i] == ',' || c[i] >= '0' && c[i] <= '9')) {
				continue;
			}
			if (c[i] == ',') {
				if (col == 0) {
					labels[r] = v;
				}
				else {
					images[r][col - 1] = v / 128.0 - 1.0;
				}
				col++;
				v = 0;
				continue;
			}
			v *= 10;
			v += c[i] - '0';
		}
		images[r][col - 1] = v / 128.0 - 1.0;
		r++;
		if (r % 439 == 0) {
			cout << r << '\n';
		}//change this
	}

}

void MNIST::dump(unsigned char *&data, int &size)
{
	size = 0;
	int i, j;

	size += sizeof this->images.size();

	for (i = 0; i < this->images.size(); i++)
		for (j = 0; j < this->images[i].size(); j++)
			size += sizeof this->images[i][j];

	for (i = 0; i < this->labels.size(); i++)
		size += sizeof this->labels[i];

	data = new unsigned char[size];

	int oneVec = (sizeof this->images[0][0]) * this->images[0].size();

	int tmp = this->images.size();
	memcpy(data, &tmp, sizeof tmp);

	for (i = 0; i < this->images.size(); i++)
		memcpy(data + sizeof tmp + i*oneVec, this->images[i].data(), oneVec);
	//for (i = 0; i < this->labels.size(); i++)
	//	memcpy(data + sizeof tmp + this->images.size()*oneVec + i*(sizeof this->labels[i]), &this->labels[i], sizeof this->labels[i]);
	memcpy(data + sizeof tmp + this->images.size()*oneVec, this->labels.data(), this->labels.size() * (sizeof this->labels[0]));

}

void MNIST::readFromDump(unsigned char *data, int size)
{
	int arraySize, i, j;
	memcpy(&arraySize, data, sizeof arraySize);
	this->images = vector<vector<double> >(arraySize);
	this->labels = vector<int>(arraySize);
	for (i = 0; i < this->images.size(); i++)
	{
		this->images[i] = vector<double>(784);
		memcpy(&this->images[i][0], data + sizeof arraySize + (i * 784 * sizeof this->images[i][0]), 784 * sizeof this->images[i][0]);
	}

	memcpy(this->labels.data(), data + sizeof arraySize + (this->images.size() * 784 * sizeof this->images[i][0]), this->labels.size() * (sizeof this->labels[i]));

}

void MNIST::dumpToFile(string location)
{
	unsigned char *data;
	int size;
	this->dump(data, size);
	FILE* file = fopen(location.c_str(), "wb");
	fwrite(data, sizeof (unsigned char), size, file);
	fclose(file);
	delete data;
}

void MNIST::readDumpFile(string location)
{
	unsigned char *data;

	FILE* file = fopen(location.c_str(), "r");
	fseek(file, 0L, SEEK_END);
	int size = ftell(file);
	rewind(file);
	data = new unsigned char[size];
	fread(data, sizeof(unsigned char), size, file);
	fclose(file);
	this->readFromDump(data, size);
	delete data;
}