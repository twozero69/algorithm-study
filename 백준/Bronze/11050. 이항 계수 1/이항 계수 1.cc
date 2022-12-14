#include <iostream>
using namespace std;

int N, K;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> K;

	int result = 1;
	for (int i = N; i >= N - K + 1; i--)
		result *= i;

	for (int i = 2; i <= K; i++)
		result /= i;

	cout << result;
	return 0;
}