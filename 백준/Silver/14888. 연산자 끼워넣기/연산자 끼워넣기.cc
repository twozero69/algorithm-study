#include <iostream>
using namespace std;
#define INT_MAX 2147483647
#define INT_MIN (-2147483647 - 1) 

int N;
int num[11];
int op[4];	//0:+, 1:-, 2:x, 3:/
int _min = INT_MAX;
int _max = INT_MIN;

void dfs(int idx, int sum) {
	int next_idx = idx + 1;
	if (next_idx == N) {
		_min = _min < sum ? _min : sum;
		_max = _max > sum ? _max : sum;
		return;
	}

	for(int i=0;i<4;i++){
		if (op[i] == 0)
			continue;

		op[i]--;
		switch (i) {
		case 0:
			dfs(next_idx, sum + num[next_idx]);
			break;
		case 1:
			dfs(next_idx, sum - num[next_idx]);
			break;
		case 2:
			dfs(next_idx, sum * num[next_idx]);
			break;
		case 3:
			dfs(next_idx, sum / num[next_idx]);
			break;
		}
		op[i]++;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> num[i];

	for (int i = 0; i < 4; i++)
		cin >> op[i];

	dfs(0, num[0]);
	cout << _max << '\n' << _min;
	return 0;
}