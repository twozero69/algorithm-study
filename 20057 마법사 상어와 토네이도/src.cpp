#include <iostream>
using namespace std;

int sand[500][500];
int N;
int result = 0;
int dy[4] = { 0, 1, 0, -1 };
int dx[4] = { -1, 0, 1, 0 };
int dir = 0;
int step = 1;
int row;
int col;
int moveTable[4][11][3] = {	//dir마다의 row, col, %를 기록
	{
		{1, 1, 1},
		{-1, 1, 1},
		{2, 0, 2},
		{-2, 0, 2},
		{0, -2, 5},
		{1, 0, 7},
		{-1, 0, 7},
		{1, -1, 10},
		{-1, -1, 10},
		{0, -1, -1},
		{0, 0, 0}
	},
	{
		{-1, 1, 1},
		{-1, -1, 1},
		{0, 2, 2},
		{0, -2, 2},
		{2, 0, 5},
		{0, 1, 7},
		{0, -1, 7},
		{1, 1, 10},
		{1, -1, 10},
		{1, 0, -1},
		{0, 0, 0}
	},
	{
		{1, -1, 1},
		{-1, -1, 1},
		{2, 0, 2},
		{-2, 0, 2},
		{0, 2, 5},
		{1, 0, 7},
		{-1, 0, 7},
		{1, 1, 10},
		{-1, 1, 10},
		{0, 1, -1},
		{0, 0, 0}
	},
	{
		{1, 1, 1},
		{1, -1, 1},
		{0, 2, 2},
		{0, -2, 2},
		{-2, 0, 5},
		{0, 1, 7},
		{0, -1, 7},
		{-1, 1, 10},
		{-1, -1, 10},
		{-1, 0, -1},
		{0, 0, 0}
	}
};

void moveSand() {
	int remainder = sand[row][col];
	for (int i = 0; i < 11; i++) {
		int sandRow = row + moveTable[dir][i][0];
		int sandCol = col + moveTable[dir][i][1];
		int moveNum;
		if (moveTable[dir][i][2] == -1) {
			moveNum = remainder;
		}
		else {
			moveNum = sand[row][col] * moveTable[dir][i][2] / 100;
			remainder -= moveNum;
		}

		if (sandRow < 0 || sandRow >= N || sandCol < 0 || sandCol >= N) {
			result += moveNum;
			continue;
		}

		sand[sandRow][sandCol] += moveNum;
	}
};

bool moveHurricane() {
	//스텝수만큼 허리케인 이동
	for (int i = 0; i < step; i++) {
		row += dy[dir];
		col += dx[dir];
		moveSand();
		if (row == 0 && col == 0)
			return false;
	}

	return true;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	row = N / 2;
	col = N / 2;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> sand[i][j];
		}
	}

	while (true) {
		//같은 스텝수로 2번이동
		if (!moveHurricane())
			break;

		//방향변경
		dir = (dir + 1) % 4;

		if (!moveHurricane())
			break;

		//방향변경
		dir = (dir + 1) % 4;

		//스텝수 변경
		step++;
	}

	cout << result;
	return 0;
}