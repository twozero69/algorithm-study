#include <iostream>
using namespace std;

int N, M;
int arr[10001];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;

	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	int left = 0, right = 0, sum = 0, count = 0;
	sum = arr[0];
	while (true) {
		if (sum == M) {
			count++;
			sum -= arr[left++];
		}
		else if (sum > M) {
			sum -= arr[left++];
		}
		else {
			sum += arr[++right];
		}

		if (right == N) {
			break;
		}
	}

	cout << count;
	return 0;
}