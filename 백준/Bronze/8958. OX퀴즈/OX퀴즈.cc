#include <iostream>
using namespace std;

int main() {
	char m[80];
	int i, j, n;
	cin >> n;
	for (i = 0; i < n; i++) {
		int sum = 0, s = 0;
		cin >> m;
		for (j = 0; j < 80; j++) {
			if (m[j] == 'O')
				sum += ++s;
			else if (m[j] == 'X')
				s = 0;
			else
				break;
		}
		cout << sum << endl;
	}
}