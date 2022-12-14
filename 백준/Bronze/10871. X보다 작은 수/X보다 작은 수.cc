#include <iostream>
using namespace std;
int main() {
	int i, n, x;
	int low[10000];
	cin >> n >> x;
	for (i = 0; i < n; i++)
		cin >> low[i];
	for (i = 0; i < n; i++) {;
	if (low[i] < x)
		cout << low[i] << " ";
	}
}