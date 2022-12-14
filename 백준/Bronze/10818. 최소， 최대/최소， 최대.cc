#include <iostream>
using namespace std;

int N;
int arr[1000000];
int _max = -1000001;
int _min = 1000001;

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
		_max = _max > arr[i] ? _max : arr[i];
		_min = _min < arr[i] ? _min : arr[i];
	}

	cout << _min << '\n' << _max;
	return 0;
}