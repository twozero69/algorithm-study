#include <iostream>
#include <queue>
using namespace std;

int N, M;
char arr[1000][1000];
bool checkEn[1000][1000] = { false, };
bool checkDis[1000][1000] = { false, };
int result = -1;

typedef struct container{
	int row;
	int col;
	bool flag;
	int depth;
}Container;

void bfs() {
	queue <Container> q;
	Container term;
	term.row = 0;
	term.col = 0;
	term.flag = true;
	term.depth = 0;
	q.push(term);

	int dy[4] = { 0,0,-1,1 };
	int dx[4] = { -1,1,0,0 };
	while (!q.empty()) {
		int row = q.front().row;
		int col = q.front().col;
		int depth = q.front().depth;
		bool flag = q.front().flag;
		q.pop();

		//테이블 범위관리
		if (row < 0 || row >= N || col < 0 || col >= M)
			continue;

		//전에 왔던 칸인지 체크
		if (checkEn[row][col])
			continue;
		else if (checkDis[row][col] && !flag)
			continue;

		//전에 오지 않았다면 이번에 왔다고 표시
		if (flag) {
			checkEn[row][col] = true;
			checkDis[row][col] = true;
		}
		else {
			checkDis[row][col] = true;
		}

		//1회 벽뚫기
		if (arr[row][col] == '1') {
			if (flag)
				flag = false;
			else
				continue;
		}

		//도착시 기록하고 종료
		if (row == N - 1 && col == M - 1) {
			result = depth + 1;
			break;
		}

		for (int i = 0; i < 4; i++) {
			Container tmp;
			tmp.row = row + dy[i];
			tmp.col = col + dx[i];
			tmp.depth = depth + 1;
			tmp.flag = flag;
			q.push(tmp);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> arr[i][j];
		}
	}

	bfs();
	cout << result;
	return 0;
}