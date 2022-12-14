#include <iostream>
using namespace std;
#define INT_MAX 2147483647


int N, M, H;
bool map[31][11];
int result = INT_MAX;

void play_game(int cnt) {
	for (int i = 1; i <= N; i++) {
		int line = i;
		for (int j = 1; j <= H; j++) {
			if (map[j][line - 1])
				line--;
			else if (map[j][line])
				line++;
		}

		if (i != line)
			return;
	}

	result = result < cnt ? result : cnt;
}

void dfs(int cnt, int row, int col, bool flag) {
	//1. 가로선 선택에 변동이 있는 경우 게임진행
	if (flag)
		play_game(cnt);

	//2. 가지치기
	if (row > H || cnt == 3)
		return;


	//4. 다음 단계로 진행
	int next_row = row;
	int next_col = col + 1;
	if (next_col == N) {
		next_row++;
		next_col = 1;
	}

	dfs(cnt, next_row, next_col, false);
	if (map[row][col] || map[row][col - 1] || map[row][col + 1])
		return;

	map[row][col] = true;
	dfs(cnt + 1, next_row, next_col, true);
	map[row][col] = false;
}

int main() {
	cin >> N >> M >> H;

	int a, b;
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		map[a][b] = true;
	}

	dfs(0, 1, 1, true);
	if (result == INT_MAX)
		cout << "-1";
	else
		cout << result;

	return 0;
}