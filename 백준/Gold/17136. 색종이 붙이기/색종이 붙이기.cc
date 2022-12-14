#include <iostream>
#include <algorithm>
#include <limits.h>
using namespace std;
int result=INT_MAX;
int __array[11][11];
int num[6];

void dfs(int x, int y, int _score) {
	if (x > 10) {
		result = min(result, _score);
		return;
	}

	if (y > 10) {
		dfs(x + 1, 1, _score);
		return;
	}

	if (__array[x][y] == 0) {
		dfs(x, y + 1, _score);
		return;
	}

	for (int i = 5; i >= 1; i--) {
		if (x + i > 11 || y + i > 11)
			continue;

		if (num[i] == 5)
			continue;

		bool flag = true;
		for (int m = 0; m < i; m++) {
			for (int n = 0; n < i; n++) {
				if (__array[x + m][y + n] == 0) {
					flag = false;
					break;
				}
			}
			if (!flag)
				break;
		}

		if (!flag)
			continue;

		for (int a = 0; a < i; a++) {
			for (int b = 0; b < i; b++) {
				__array[x + a][y + b] = 0;
			}
		}

		num[i]++;
		dfs(x, y + i, _score + 1);


		
		for (int a = 0; a < i; a++) {
			for (int b = 0; b < i; b++) {
				__array[x + a][y + b] = 1;
			}
		}
		num[i]--;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int term;
	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= 10; j++) {
			cin >> term;
			__array[i][j] = term;
		}
	}

	dfs(1, 1, 0);

	if (result == INT_MAX)
		cout << -1;
	else
		cout << result;
}