#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<short> tall;
vector<short> real;

int main() {
	short a;
	for (int i = 0; i < 9; i++) {
		scanf("%hd", &a);
		tall.push_back(a);
	}

	do {
		int sum = 0;
		for (int j = 0; j < 7; j++) {
			sum += tall[j];
		}
		if (sum == 100) {
			for (int m = 0; m < 7; m++) {
				real.push_back(tall[m]);
			}
			break;
		}
	} while (next_permutation(tall.begin(), tall.end()));

	sort(real.begin(), real.end());

 
	for (int k = 0; k < 7; k++) {
		if (!real.empty())
			printf("%hd\n", real[k]);
		else
			printf("%hd\n", tall[k]);
	}
}