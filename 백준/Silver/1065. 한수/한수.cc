#include <iostream>
using namespace std;
int main() {
	int a, b, c, n, i, sum = 0;
	cin >> n;
	for (i = 1; i <= n; i++) {
		if (i < 100) {
			sum++;
			continue;
		}
		else if (i == 1000)
			break;
		a = (i % 1000) / 100;
		b = (i % 100) / 10;
		c = i % 10;
		if (a - b == b - c)
			sum++;
	}
	cout << sum;
}