#include <iostream>
using namespace std;

int main() {
	int i, a[8], s = 0;
	for (i = 0; i < 8; i++) {
		cin >> a[i];
		if (a[i] == i + 1)
			s++;
		else if (a[i] == 8 - i)
			s--;
	}
	if (s == 8)
		cout << "ascending";
	else if (s == -8)
		cout << "descending";
	else
		cout << "mixed";
}