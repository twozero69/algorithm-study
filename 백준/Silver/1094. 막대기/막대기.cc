#include <iostream>
using namespace std;

int x;
int result;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> x;

	while (x) {
		if (x % 2)
			result++;
		x >>= 1;
	}

	cout << result;
}