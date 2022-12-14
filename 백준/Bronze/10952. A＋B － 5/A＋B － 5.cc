#include <iostream>
using namespace std;

int A, B;

int main() {
	while (true) {
		cin >> A >> B;
		if (A == 0 && B == 0)
			break;
		cout << A + B << '\n';
	}
}