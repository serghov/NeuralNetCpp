#define _CRT_SECURE_NO_WARNINGS

#include "MNIST.h"

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
					images[r][col - 1] = v / 256.0;
				}
				col++;
				v = 0;
				continue;
			}
			v *= 10;
			v += c[i] - '0';
		}
		images[r][col - 1] = v / 256.0;
		r++;
		if (r % 439 == 0) {
			cout << r << '\n';
		}//change this code, doesnt work on small numbers no time to check why
	}
}