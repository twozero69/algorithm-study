#include <iostream>
#include <algorithm>
using namespace std;

int v[502][502];
int N, M;
int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };
int high_score;

void dfs(int count, int x, int y, int result, int direction) {
	if (count >= 4) {
		high_score = max(result, high_score);
		return;
	}

	if (v[x][y]) {
		for (int i = 0; i < 4; i++) {
			switch (direction) {
			case 0:if (i == 1)continue; break;
			case 1:if (i == 0)continue; break;
			case 2:if (i == 3)continue; break;
			case 3:if (i == 2)continue; break;
			}
			dfs(count + 1, x + dx[i], y + dy[i], result + v[x][y], i);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;

	int a;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> a;
			v[i][j]=a;
		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			dfs(0, i, j, 0, 4);
		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			int score = v[i][j]+v[i+1][j]+v[i-1][j]+v[i][j+1]+v[i][j-1];
			for (int k = 0; k < 4; k++)
				high_score = max(high_score, score - v[i + dx[k]][j + dy[k]]);
		}
	}

	cout << high_score;
}