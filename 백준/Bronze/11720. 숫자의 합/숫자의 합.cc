#include <iostream>
using namespace std;

int main() {
	int c,sum=0;
	char n;
	cin >> c;
	for (int i = 0; i < c; i++) {
		cin >> n;
		sum += (n-48) % 10;
	}
	cout << sum;
}