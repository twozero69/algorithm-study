#include <iostream>
#include <queue>
using namespace std;

typedef struct fireball {
	int m;
	int speed;
	int dir;
	int round = 0;
}FIREBALL;

int N, M, K;
queue<FIREBALL> fireballs[50][50];
int dy[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dx[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
int evenOddDir[4] = { 0, 2, 4, 6 };
int normalDir[4] = { 1, 3, 5, 7 };

int findNextRow(int row, int dir, int speed) {
	int step = speed % N;
	return (row + N + dy[dir] * step) % N;
}

int findNextCol(int col, int dir, int speed) {
	int step = speed % N;
	return (col + N + dx[dir] * step) % N;
}

void moveFireball(int row, int col, int round) {
	while (!fireballs[row][col].empty()) {
		FIREBALL term = fireballs[row][col].front();
		if (term.round >= round)
			break;

		fireballs[row][col].pop();
		int nextRow = findNextRow(row, term.dir, term.speed);
		int nextCol = findNextCol(col, term.dir, term.speed);
		term.round = round;
		fireballs[nextRow][nextCol].push(term);
	}
}

void divideFireball(int row, int col, int round) {
	bool oddFlag = true;
	bool evenFlag = true;
	int sumM = 0;
	int sumSpeed = 0;
	int fireballNum = fireballs[row][col].size();

	while (!fireballs[row][col].empty()) {
		FIREBALL term = fireballs[row][col].front();
		fireballs[row][col].pop();

		if (term.dir % 2 == 0)	//짝수
			oddFlag = false;
		else  //홀수
			evenFlag = false;

		sumM += term.m;
		sumSpeed += term.speed;
	}

	int newSpeed = sumSpeed / fireballNum;
	int newM = sumM / 5;
	if (newM == 0)
		return;

	for (int i = 0; i < 4; i++) {
		FIREBALL newBall;
		newBall.round = round;
		newBall.speed = newSpeed;
		newBall.m = newM;
		if (oddFlag || evenFlag)
			newBall.dir = evenOddDir[i];
		else
			newBall.dir = normalDir[i];
		fireballs[row][col].push(newBall);
	}
}

void playgame(int round) {
	//파이어볼을 이동
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (fireballs[i][j].empty())
				continue;

			moveFireball(i, j, round);
		}
	}

	//파이어볼을 나눔
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (fireballs[i][j].size() < 2)
				continue;

			divideFireball(i, j, round);
		}
	}
}

int getResult() {
	int result = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			while (!fireballs[i][j].empty()) {
				result += fireballs[i][j].front().m;
				fireballs[i][j].pop();
			}
		}
	}

	return result;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M >> K;
	for (int i = 0; i < M; i++) {
		FIREBALL term;
		int row, col;
		cin >> row >> col >> term.m >> term.speed >> term.dir;
		fireballs[row - 1][col - 1].push(term);
	}

	for (int i = 1; i <= K; i++) {
		playgame(i);
	}

	cout << getResult();
	return 0;
};