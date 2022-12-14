#include <iostream>
using namespace std;

int main() {
	int i, a[3], p = 1, e[10];
	for (i = 0; i < 3; i++) {
		cin >> a[i];
		p *= a[i];
	}
	for (i = 0; i < 10; i++)
		e[i] = 0;
	while (true) {
		for (i = 0; i < 10; i++)
			if (p % 10 == i)
				e[i]++;
		p /= 10;
		if (p == 0)
			break;
	}
	for (i = 0; i < 10; i++)
		cout << e[i] << endl;
}