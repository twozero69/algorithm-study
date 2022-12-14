#include <iostream>
using namespace std;

int N = 0, M = 0;	//3~50

int r = 0, c = 0, d = 0;
int arr[50][50] = { {0,}, };	//0은 빈칸 1은 벽, 테두리는 무조건 벽
bool check[50][50] = { {false, }, };
int result = 0;

int dx[4] = { 0, 1, 0, -1 };//0123 북동남서
int dy[4] = { -1, 0, 1, 0 };

bool dfs(int row, int col, int dir, bool back){
	if (row < 0 || row >= N)
		return false;
	if (col < 0 || col >= M)
		return false;
	
	if (!back) {	//일반탐색
		if (check[row][col] || arr[row][col] == 1)
			return false;

		//일단 현재위치를 청소
		check[row][col] = true;
		result++;
	}
	else {	//후진탐색
		if (arr[row][col] == 1)
			return false;
	}

	//로봇청소기의 움직임구현
	bool flag = false;
	for (int i = 0; i < 4; i++) {	//회전구현
		dir = (dir + 3) % 4;
		if (dfs(row + dy[dir], col + dx[dir], dir, false)) {
			flag = true;
			break;
		}
	}

	if (!flag) {	//후진구현
		int backdir = (dir + 2) % 4;
		dfs(row + dy[backdir], col + dx[backdir], dir, true);
	}

	return true;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	cin >> r >> c >> d;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> arr[i][j];
		}
	}

	dfs(r, c, d, false);
	cout << result;
	return 0;
}