#include <iostream>
using namespace std;

int num[9];
int idx = -1;
int _max = -1;

int main() {
	for (int i = 1; i <= 9; i++) {
		cin >> num[i];
		if (_max < num[i]) {
			_max = num[i];
			idx = i;
		}
	}

	cout << _max << '\n' << idx;
	return 0;
}