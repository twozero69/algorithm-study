#include <iostream>
using namespace std;

int N, L;
int map[100][100];
int result = 0;

void dfs(int idx, int floor, int cnt, int dir, int no) {
	if (idx == N) {
		result++;
		return;
	}
	
	int current_floor = 0;
	if (dir == 0)
		current_floor = map[no][idx];
	else if (dir == 1)
		current_floor = map[idx][no];

	switch (current_floor - floor) {
	case 0: //같은 층
		dfs(idx + 1, current_floor, cnt + 1, dir, no);
		break;
	case 1:	//위로
		if (cnt < L)
			return;

		dfs(idx + 1, current_floor, 1, dir, no);
		break;
	case -1: //아래로
		if (idx + L > N)
			return;

		for (int i = 1; i < L; i++) {
			if (dir == 0) {
				if (current_floor != map[no][idx + i])
					return;
			}
			else if (dir == 1) {
				if (current_floor != map[idx + i][no])
					return;
			}
		}

		dfs(idx + L, current_floor, 0, dir, no);
		break;
	}
}

int main() {
	cin >> N >> L;
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < N; i++)
		dfs(0, map[i][0], 0, 0, i);

	for (int i = 0; i < N; i++)
		dfs(0, map[0][i], 0, 1, i);

	cout << result;
	return 0;
}