#include <iostream>
#include <vector>
using namespace std;

int N, M;
int map[49][49];
int _hash[49][49]; //row, col을 idx로 변환
int result = 0;
vector<int> balls;
int full;
int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };
int mapDy[4] = { 0, 1, 0, -1 };
int mapDx[4] = { -1, 0, 1, 0 };

void printMap() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int idx = _hash[i][j];
			if (balls.size() <= idx)
				cout << 0 << ' ';
			else
				cout << balls[idx] << ' ';
		}
		cout << '\n';
	}
	
	for (int i = 0; i < balls.size(); i++) {
		cout << balls[i] << ' ';
	}

	cout << balls.size() << "\n\n";
}

bool oneStraight(int& row, int& col, int step, int& cnt, int& dir) {
	for (int i = 0; i < step; i++) {
		row += mapDy[dir];
		col += mapDx[dir];

		if (row < 0 || row >= N || col < 0 || col >= N)
			return false;

		balls.push_back(map[row][col]);
		_hash[row][col] = cnt++;
	}

	dir = (dir + 1) % 4;
	return true;
}

bool twoStraight(int& row, int& col, int& step, int& cnt, int& dir) {
	for (int i = 0; i < 2; i++) {
		if (!oneStraight(row, col, step, cnt, dir))
			return false;
	}
	step++;
	return true;
}

void map2Linear() {
	int mapDir = 0;
	int row = N / 2;
	int col = N / 2;
	int cnt = 0;
	int step = 1;
	while (twoStraight(row, col, step, cnt, mapDir));
	for (int i = 0; i < balls.size(); i++) {
		if (balls[i] != 0)
			continue;

		balls.erase(balls.begin() + i);
		i--;
	}
}

void breakBalls(int dir, int step) {
	int row = N / 2;
	int col = N / 2;
	for (int i = 0; i < step; i++) {
		row += dy[dir];
		col += dx[dir];

		if (row < 0 || row >= N || col < 0 || col >= N)
			break;

		int idx = _hash[row][col];
		if (balls.size() > idx)
			balls[idx] = 0;
	}

	for (int i = 0; i < balls.size(); i++) {
		if (balls[i] == 0) {
			balls.erase(balls.begin() + i);
			i--;
		}
	}
}

bool explosion() {
	int stackNum = 0;
	int stackSize = 0;
	int startIdx = 0;
	bool restartFlag = false;
	
	for (int i = 0; i < balls.size(); i++) {
		if (stackNum != balls[i]) {
			if (stackSize >= 4) {
				restartFlag = true;
				result += stackSize * stackNum;
				for (int j = 0; j < stackSize; j++) {
					balls[startIdx + j] = 0;
				}
			}

			stackSize = 1;
			startIdx = i;
			stackNum = balls[i];
		}
		else {
			stackSize++;
		}
	}

	if (stackSize >= 4) {
		restartFlag = true;
		result += stackSize * stackNum;
		for (int j = 0; j < stackSize; j++) {
			balls[startIdx + j] = 0;
		}
	}

	for (int i = 0; i < balls.size(); i++) {
		if (balls[i] != 0)
			continue;

		balls.erase(balls.begin() + i);
		i--;
	}

	return restartFlag;
}

void changeBalls() {
	vector<int> groupInfo;	//first: 그룹사이즈, second: 그룹의 구슬번호
	int stackNum = 0;
	int stackSize = 0;
	for (int i = 0; i < balls.size(); i++) {
		if (balls[i] != stackNum) {
			if (stackSize != 0) {
				groupInfo.push_back(stackSize);
				groupInfo.push_back(stackNum);
			}

			stackSize = 1;
			stackNum = balls[i];
		}
		else {
			stackSize++;
		}
	}

	if (stackSize != 0) {
		groupInfo.push_back(stackSize);
		groupInfo.push_back(stackNum);
	}

	balls.clear();
	for (int i = 0; i < groupInfo.size(); i++) {
		if (balls.size() >= full)
			return;

		balls.push_back(groupInfo[i]);
	}
}

void blizzard(int dir, int step) {
	//1. 구슬 부수기
	breakBalls(dir, step);

	//2. 연속하는 구슬을 폭파
	while (explosion());
	
	//3. 구슬을 변경
	changeBalls();

	//4. 폭파
	while(explosion());
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	full = N * N - 1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	map2Linear();

	for (int i = 0; i < M; i++) {
		int dir, step;
		cin >> dir >> step;
		blizzard(dir - 1, step);
	}

	cout << result;
	return 0;
}