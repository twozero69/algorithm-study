#include <iostream>
#include <math.h>
using namespace std;


int N, L, R;
int arr[50][50];
int map[50][50];
bool check[50][50];
int dy[4] = { 0,0,-1,1 };
int dx[4] = { -1,1,0,0 };
int countrys[2500];
int population[2500];


void reset() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			check[i][j] = false;
			map[i][j] = 0;
		}
	}

	for (int i = 0; i < N * N; i++) {
		countrys[i] = 0;
		population[i] = 0;
	}
}


void dfs(int row, int col, int popul, int idx) {
	if (row < 0 || row >= N || col < 0 || col >= N)
		return;

	if (check[row][col])
		return;

	int term = abs(arr[row][col] - popul);
	if ((L > term || term > R) && popul != -1)
		return;

	check[row][col] = true;
	map[row][col] = idx;
	countrys[idx]++;
	population[idx] += arr[row][col];

	for (int i = 0; i < 4; i++) {
		dfs(row + dy[i], col + dx[i], arr[row][col], idx);
	}
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> L >> R;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
		}
	}

	int cnt = 0;

	while (true) {
		//0. 초기화
		reset();
		int idx = 0;

		//1. 덩어리 분류
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (check[i][j])
					continue;

				dfs(i, j, -1, idx);
				idx++;
			}
		}

		//2. 종료조건 체크
		if (idx == N * N)
			break;

		//3. 인구분배
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				arr[i][j] = population[map[i][j]] / countrys[map[i][j]];
			}
		}

		cnt++;
	}

	cout << cnt;
	return 0;
}