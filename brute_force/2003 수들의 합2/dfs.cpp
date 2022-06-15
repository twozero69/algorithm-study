#include <iostream>
using namespace std;

int N, M;
int arr[10000];
int result = 0;

void dfs(int idx, int sum) {
	if (sum >= M) {
		if (sum == M) {
			result++;
		}

		return;
	}

	int next = idx + 1;
	if (next < N) {
		dfs(next, sum + arr[next]);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	for (int i = 0; i < N; i++) {
		dfs(i, arr[i]);
	}

	cout << result;

	return 0;
}