#include <iostream>
using namespace std;
int main() {
	int m, n,min=0, i = 1, sum = 0;
	cin >> m >> n;
	while (n > i) {
		if ((n >= i * i) && (i*i >= m)) {
			if (sum == 0)
				min = i * i;
			sum += i * i;
		}
		i++;
	}
	if (sum == 0) {
		cout << "-1";
		return 0;
	}
	cout << sum << endl << min;
}