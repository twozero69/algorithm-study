#include <iostream>
using namespace std;
int main() {
	int x, n, i = 0;
	cin >> x;
	n = x;

	while (true) {
		i++;
		x = ((x % 10) * 10 + ((x % 10) + (x / 10))%10);
		if (n == x) {
			cout << i;
			break;
		}
	}
}