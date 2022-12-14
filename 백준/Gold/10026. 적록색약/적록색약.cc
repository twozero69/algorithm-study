#include <iostream>
using namespace std;

int N = 0;
char arr[100][100];
int dy[4] = {0,0,-1,1};
int dx[4] = {-1,1,0,0};
int normal = 0;
int redgreen = 0;
bool checknormal[100][100] = { {false,}, };
bool checkredgreen[100][100] = { {false,}, };

void dfs(int row, int col, bool normal, char character) {
	if (row < 0 || row >= N || col < 0 || col >= N)
		return;

	if (normal) {
		if (checknormal[row][col])
			return;

		if (arr[row][col] != character)
			return;

		checknormal[row][col] = true;
	}
	else {
		if (checkredgreen[row][col])
			return;

		switch (character) {
		case 'R':
		case 'G':
			if (arr[row][col] == 'B')
				return;
			break;
		case 'B':
			if (arr[row][col] != 'B')
				return;
			break;
		}

		checkredgreen[row][col] = true;
	}
	

	for (int i = 0; i < 4; i++) {
		dfs(row + dy[i], col + dx[i], normal, arr[row][col]);
	}
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (!checknormal[i][j]) {
				dfs(i, j, true, arr[i][j]);
				normal++;
			}
			if (!checkredgreen[i][j]) {
				dfs(i, j, false, arr[i][j]);
				redgreen++;
			}
		}
	}

	cout << normal << ' ' << redgreen;
	return 0;
}