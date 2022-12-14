#include <iostream>
using namespace std;
#define INT_MAX 2147483647

int N, M;
int card[100];
int min_ = INT_MAX;
int container = 0;
int result = 0;

void dfs(int count, int idx) {
	if (count == 3) {
		int tmp = M-container;
		if (min_ > tmp && tmp >= 0) {
			min_ = tmp;
			result = container;
		}
		return;
	}

	if (idx == N)
		return;

	dfs(count, idx + 1);
	container += card[idx];
	dfs(count + 1, idx + 1);
	container -= card[idx];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < N; i++)
		cin >> card[i];

	dfs(0, 0);
	cout << result;
	return 0;
}