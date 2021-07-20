#include <iostream>
#define INT_MAX 100001
using namespace std;

int N, S;
int arr[100001];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> S;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	int left = 0, right = 0;
	int sum = arr[0];
	int count = 1;
	int minCount = INT_MAX;

	while (true) {
		if (sum >= S) {
			minCount = minCount < count ? minCount : count;
			sum -= arr[left++];
			count--;
		}
		else {
			sum += arr[++right];
			count++;
		}

		if (right == N) {
			break;
		}
	}

	if (minCount == INT_MAX)
		cout << 0;
	else
		cout << minCount;

	return 0;
}