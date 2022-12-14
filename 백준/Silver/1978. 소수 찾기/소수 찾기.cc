#include <iostream>
using namespace std;

int N;	//100이하
bool sosu[1001];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	for (int i = 2; i < 1001; i++) {
		bool flag = true;
		for (int j = 2; j < i; j++) {
			if (i % j == 0) {
				flag = false;
				break;
			}
		}

		sosu[i] = flag;
	}

	cin >> N;
	int term;
	int result = 0;
	for (int i = 0; i < N; i++) {
		cin >> term;
		if (sosu[term])
			result++;
	}

	cout << result;
	return 0;
}