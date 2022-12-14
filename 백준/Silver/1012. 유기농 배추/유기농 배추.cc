#include <iostream>
using namespace std;

int T;//테스트 케이스의 개수
int M;//밭의 가로길이-x
int N;//밭의 세로길이-y
int K;//심어진 배추의 개수

int arr[50][50];
int _count;

void dfs(int x, int y) {
	if (0 > x || x >= M)
		return;

	if (0 > y || y >= N)
		return;

	if (arr[y][x] != 1)
		return;

	arr[y][x] = 0;

	dfs(x, y + 1);
	dfs(x, y - 1);
	dfs(x + 1, y);
	dfs(x - 1, y);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> T;
	for (int t = 0; t < T; t++) {
		cin >> M >> N >> K;
		//초기화
		for (int n = 0; n < N; n++) {
			for (int m = 0; m < M; m++) {
				arr[n][m] = 0;
			}
		}

		_count = 0;

		int x, y;
		for (int k = 0; k < K; k++) {
			cin >> x >> y;
			arr[y][x] = 1;
		}

		for (int n = 0; n < N; n++) {
			for (int m = 0; m < M; m++) {
				if (arr[n][m] == 1) {
					_count++;
					dfs(m, n);
				}
			}
		}

		cout << _count << endl;
	}

	return 0;
}