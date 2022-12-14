#include <iostream>
using namespace std;

int N;//보드의 크기 1~20;
int table[20][20];
int result = -1;
//0-좌, 1-우, 2-상, 3-하
int dy[4] = { 0,0,-1,1 };
int dx[4] = { -1,1,0,0 };

void moveLeft() {
	for (int row = 0; row < N; row++) {
		int limit = 0;
		for (int col = 0; col < N; col++) {
			if (table[row][col] == 0)
				continue;

			int value = table[row][col];
			int newCol = col + dx[0];
			bool flag = true;

			//블록을 체크
			while (newCol >= limit) {
				//블록 발견
				if (table[row][newCol] != 0) {
					//같은 값인 블록 2개가 만나서 합쳐지는 경우
					if (table[row][newCol] == value) {
						table[row][col] = 0;
						table[row][newCol] = value * 2;
						limit = newCol + dx[1];	//이미 합쳐진 블록은 다시 합쳐지지 않게하기 위함.
						flag = false;
						break;
					}
					//블록들이 합쳐지지 않는 경우
					else {
						//while문 밖에서 블록을 발견하지 못한 경우와 일괄처리
						break;
					}
				}

				newCol += dx[0];
			}

			//끝까지 블록을 발견하지 못한경우(newCol=-1) + 블록을 발견했으나 합쳐지지 않은 경우(newCol=발견한 블록의 위치)
			if (flag) {
				table[row][col] = 0;
				table[row][newCol + dx[1]] = value;
			}
		}
	}
}

void moveRight() {
	for (int row = 0; row < N; row++) {
		int limit = N;
		for (int col = N-1; col >= 0; col--) {
			if (table[row][col] == 0)
				continue;

			int value = table[row][col];
			int newCol = col + dx[1];
			bool flag = true;

			//블록을 체크
			while (newCol < limit) {
				//블록 발견
				if (table[row][newCol] != 0) {
					//같은 값인 블록 2개가 만나서 합쳐지는 경우
					if (table[row][newCol] == value) {
						table[row][col] = 0;
						table[row][newCol] = value * 2;
						flag = false;
						limit = newCol;	//이미 합쳐진 블록은 다시 합쳐지지 않게하기 위함.
						break;
					}
					//블록들이 합쳐지지 않는 경우
					else {
						//while문 밖에서 블록을 발견하지 못한 경우와 일괄처리
						break;
					}
				}

				newCol += dx[1];
			}

			//블록을 발견하지 못한경우(newCol=N) + 블록을 발견했으나 합쳐지지 않은 경우(newCol=발견한 블록의 위치)
			if (flag) {
				table[row][col] = 0;
				table[row][newCol + dx[0]] = value;
			}
		}
	}
}

void moveUp() {
	for (int col = 0; col < N; col++) {
		int limit = 0;
		for (int row = 0; row < N; row++) {
			if (table[row][col] == 0)
				continue;

			int value = table[row][col];
			int newRow = row + dy[2];
			bool flag = true;

			//블록을 체크
			while (newRow >= limit) {
				//블록 발견
				if (table[newRow][col] != 0) {
					//같은 값인 블록 2개가 만나서 합쳐지는 경우
					if (table[newRow][col] == value) {
						table[row][col] = 0;
						table[newRow][col] = value * 2;
						flag = false;
						limit = newRow + dy[3];	//이미 합쳐진 블록은 다시 합쳐지지 않게하기 위함.
						break;
					}
					//블록들이 합쳐지지 않는 경우
					else {
						//while문 밖에서 블록을 발견하지 못한 경우와 일괄처리
						break;
					}
				}

				newRow += dy[2];
			}

			//끝까지 블록을 발견하지 못한경우(newRow=-1) + 블록을 발견했으나 합쳐지지 않은 경우(newRow=발견한 블록의 위치)
			if (flag) {
				table[row][col] = 0;
				table[newRow+dy[3]][col] = value;
			}
		}
	}
}

void moveDown() {
	for (int col = 0; col < N; col++) {
		int limit = N;
		for (int row = N - 1; row >= 0; row--) {
			if (table[row][col] == 0)
				continue;

			int value = table[row][col];
			int newRow = row + dy[3];
			bool flag = true;

			//블록을 체크
			while (newRow < limit) {
				//블록 발견
				if (table[newRow][col] != 0) {
					//같은 값인 블록 2개가 만나서 합쳐지는 경우
					if (table[newRow][col] == value) {
						table[row][col] = 0;
						table[newRow][col] = value * 2;
						flag = false;
						limit = newRow;	//이미 합쳐진 블록은 다시 합쳐지지 않게하기 위함.
						break;
					}
					//블록들이 합쳐지지 않는 경우
					else {
						//while문 밖에서 블록을 발견하지 못한 경우와 일괄처리
						break;
					}
				}

				newRow += dy[3];
			}

			//블록을 발견하지 못한경우(newRow=N) + 블록을 발견했으나 합쳐지지 않은 경우(newRow=발견한 블록의 위치)
			if (flag) {
				table[row][col] = 0;
				table[newRow+dy[2]][col] = value;
			}
		}
	}
}

void moveTable(int dir) {
	switch (dir) {
	case 0:
		moveLeft();
		break;
	case 1:
		moveRight();
		break;
	case 2:
		moveUp();
		break;
	case 3:
		moveDown();
		break;
	}
}

void checkMax() {
	int max = -1;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (table[i][j] > max)
				max = table[i][j];
		}
	}

	result = result > max ? result : max;
}

void dfs(int cnt) {
	if (cnt == 5) {
		checkMax();
		return;
	}

	//복원데이터 저장
	int recovery[20][20];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			recovery[i][j] = table[i][j];
		}
	}

	
	for (int dir = 0; dir < 4; dir++) {
		//다음단계로 진행
		moveTable(dir);
		dfs(cnt + 1);

		//복원
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				table[i][j] = recovery[i][j];
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> table[i][j];
		}
	}

	dfs(0);
	cout << result;
	return 0;
}