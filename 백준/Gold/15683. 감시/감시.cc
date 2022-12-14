#include <iostream>
#include <vector>
using namespace std;
#define INT_MAX 2147483647


typedef struct cctv {
	int row;
	int col;
	char type;
}CCTV;


int N, M;
char map[8][8];
vector<CCTV> cctvs;
int result = INT_MAX;


int dy[4] = { -1,0,1,0 };	//시계방향 0-상, 1-우, 2-하, 3-좌
int dx[4] = { 0,1,0,-1 };


void check_result() {
	int sum = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 0)
				sum++;
		}
	}

	result = result < sum ? result : sum;
}


void set_value(int row, int col, int dir, char value) {
	if (row < 0 || row >= N || col < 0 || col >= M)
		return;

	if (map[row][col] == '6')
		return;

	if (map[row][col] < 10) {
		switch (value) {
		case '#':
			map[row][col]++;
			break;
		case '0':
			map[row][col]--;
			break;
		}
	}

	set_value(row + dy[dir], col + dx[dir], dir, value);
}


void dfs(int idx) {
	if (idx == cctvs.size()) {
		check_result();
		return;
	}

	CCTV cctv = cctvs[idx];
	switch (cctv.type) {
		case '1': {	//1개 방향
			for (int dir = 0; dir < 4; dir++) {
				set_value(cctv.row + dy[dir], cctv.col + dx[dir], dir, '#');
				dfs(idx + 1);
				set_value(cctv.row + dy[dir], cctv.col + dx[dir], dir, '0');
			}
			break;
		}
		case '2': {	//2개 방향 일자
			for (int dir1 = 0; dir1 < 2; dir1++) {
				int dir2 = dir1 + 2;
				set_value(cctv.row + dy[dir1], cctv.col + dx[dir1], dir1, '#');
				set_value(cctv.row + dy[dir2], cctv.col + dx[dir2], dir2, '#');
				dfs(idx + 1);
				set_value(cctv.row + dy[dir1], cctv.col + dx[dir1], dir1, '0');
				set_value(cctv.row + dy[dir2], cctv.col + dx[dir2], dir2, '0');
			}
			break;
		}
		case '3': {	//2개 방향 직각
			for (int dir1 = 0; dir1 < 4; dir1++) {
				int dir2 = (dir1 + 1) % 4;
				set_value(cctv.row + dy[dir1], cctv.col + dx[dir1], dir1, '#');
				set_value(cctv.row + dy[dir2], cctv.col + dx[dir2], dir2, '#');
				dfs(idx + 1);
				set_value(cctv.row + dy[dir1], cctv.col + dx[dir1], dir1, '0');
				set_value(cctv.row + dy[dir2], cctv.col + dx[dir2], dir2, '0');
			}
			break;
		}
		case '4': {	//3개 방향
			for (int dir1 = 0; dir1 < 4; dir1++) {
				int dir2 = (dir1 + 1) % 4;
				int dir3 = (dir1 + 2) % 4;
				set_value(cctv.row + dy[dir1], cctv.col + dx[dir1], dir1, '#');
				set_value(cctv.row + dy[dir2], cctv.col + dx[dir2], dir2, '#');
				set_value(cctv.row + dy[dir3], cctv.col + dx[dir3], dir3, '#');
				dfs(idx + 1);
				set_value(cctv.row + dy[dir1], cctv.col + dx[dir1], dir1, '0');
				set_value(cctv.row + dy[dir2], cctv.col + dx[dir2], dir2, '0');
				set_value(cctv.row + dy[dir3], cctv.col + dx[dir3], dir3, '0');
			}
			break;
		}
		case '5': {	//4개 방향
			set_value(cctv.row + dy[0], cctv.col + dx[0], 0, '#');
			set_value(cctv.row + dy[1], cctv.col + dx[1], 1, '#');
			set_value(cctv.row + dy[2], cctv.col + dx[2], 2, '#');
			set_value(cctv.row + dy[3], cctv.col + dx[3], 3, '#');
			dfs(idx + 1);
			set_value(cctv.row + dy[0], cctv.col + dx[0], 0, '0');
			set_value(cctv.row + dy[1], cctv.col + dx[1], 1, '0');
			set_value(cctv.row + dy[2], cctv.col + dx[2], 2, '0');
			set_value(cctv.row + dy[3], cctv.col + dx[3], 3, '0');
			break;
		}
	}
}


int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == '6')
				continue;

			if (map[i][j] == '0') {
				map[i][j] = 0;
				continue;
			}

			CCTV cctv;
			cctv.row = i;
			cctv.col = j;
			cctv.type = map[i][j];
			cctvs.push_back(cctv);
		}
	}


	dfs(0);
	cout << result;
	return 0;
}