#include <iostream>
using namespace std;

typedef struct fish {
	int num;
	int dir;
	bool alive = true;
}FISH;

FISH fishes[4][4];
pair<int, int> _hash[16];
int dy[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dx[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };
int result = 0;

void tradeFish(int rowA, int colA, int rowB, int colB) {
	FISH term = fishes[rowA][colA];
	fishes[rowA][colA] = fishes[rowB][colB];
	fishes[rowB][colB] = term;
}

void tradeHash(int numA, int numB) {
	pair<int, int> term(_hash[numA]);
	_hash[numA] = _hash[numB];
	_hash[numB] = term;
}

void dfs(int row, int col, int dir, int sum) {
	//1. 카피생성
	FISH fishesCopy[4][4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			fishesCopy[i][j] = fishes[i][j];
		}
	}

	pair<int, int> hashCopy[16];
	for (int i = 0; i < 16; i++) {
		hashCopy[i] = _hash[i];
	}

	//2. 물고기 이동
	for (int i = 0; i < 16; i++) {
		pair<int, int> fishPos = _hash[i];
		FISH fish = fishes[fishPos.first][fishPos.second];

		if (!fish.alive)
			continue;

		for (int j = 0; j < 8; j++) {
			int newDir = (fish.dir + j) % 8;
			int newFishRow = fishPos.first + dy[newDir];
			int newFishCol = fishPos.second + dx[newDir];
			int newFishNum = fishes[newFishRow][newFishCol].num;

			//이동불가-경계를 벗어남
			if (newFishRow < 0 || newFishRow >= 4 || newFishCol < 0 || newFishCol >= 4)
				continue;

			//이동불가-상어위치
			if (newFishRow == row && newFishCol == col)
				continue;

			//이동가능-물고기칸, 빈칸(결국에 빈칸이란 죽은 물고기칸임)
			fishes[fishPos.first][fishPos.second].dir = newDir;
			tradeFish(newFishRow, newFishCol, fishPos.first, fishPos.second);
			tradeHash(newFishNum, i);
			break;
		}
	}

	//3. 상어 이동
	bool endFlag = true;
	for (int i = 1; i <= 3; i++) {
		int newRow = row + i * dy[dir];
		int newCol = col + i * dx[dir];
		if (newRow < 0 || newRow >= 4 || newCol < 0 || newCol >= 4)
			break;

		if (!fishes[newRow][newCol].alive)
			continue;

		fishes[newRow][newCol].alive = false;
		dfs(newRow, newCol, fishes[newRow][newCol].dir, sum + fishes[newRow][newCol].num + 1);
		fishes[newRow][newCol].alive = true;
		endFlag = false;
	}

	if (endFlag)
		result = result > sum ? result : sum;

	//4. 데이터 복구
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			fishes[i][j] = fishesCopy[i][j];
		}
	}

	for (int i = 0; i < 16; i++) {
		_hash[i] = hashCopy[i];
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int fishNum, fishDir;
			cin >> fishNum >> fishDir;

			fishes[i][j].num = --fishNum;
			fishes[i][j].dir = --fishDir;
			
			_hash[fishNum].first = i;
			_hash[fishNum].second = j;
		}
	}

	fishes[0][0].alive = false;
	dfs(0, 0, fishes[0][0].dir, fishes[0][0].num + 1);
	cout << result;
	return 0;
}