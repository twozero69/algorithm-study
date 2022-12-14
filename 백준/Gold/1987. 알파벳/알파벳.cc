#include <iostream>
using namespace std;

int R, C;
char arr[20][20];
bool check[26] = {false, };
int result = -1;
int dy[4] = { 0,0,-1,1 };
int dx[4] = { -1,1,0,0 };

void dfs(int cnt, int row, int col) {
	if (row < 0 || row >= R || col < 0 || col >= C || check[arr[row][col] - 65]) {
		result = result > cnt ? result : cnt;
		return;
	}

	check[arr[row][col] - 65] = true;
	for (int i = 0; i < 4; i++) {
		dfs(cnt+1, row + dy[i], col + dx[i]);
	}
	check[arr[row][col] - 65] = false;
}
	
int main() {
	cin >> R >> C;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> arr[i][j];
		}
	}

	dfs(0, 0, 0);
	cout << result;
	return 0;
}