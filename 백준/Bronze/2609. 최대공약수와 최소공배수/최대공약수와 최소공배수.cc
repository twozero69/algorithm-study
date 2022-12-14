#include <iostream>
using namespace std;

int num1, num2;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> num1 >> num2;
	int max = num1 > num2 ? num1 : num2;
	for (int i = max; i >= 1; i--) {
		if (num1 % i == 0 && num2 % i == 0) {
			cout << i << '\n';
			break;
		}
	}

	int tmp1 = num1;
	int tmp2 = num2;
	int weight1 = 1;
	int weight2 = 1;
	while (tmp1 != tmp2) {
		if (tmp1 < tmp2) {
			tmp1 = num1 * ++weight1;
		}
		else {
			tmp2 = num2 * ++weight2;
		}
	}
	cout << tmp1;
	return 0;
}