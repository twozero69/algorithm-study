#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

int N, Q;
int gridSize;
int grid[64][64];
int dy[4] = { 0, 0, -1, 1 };
int dx[4] = { -1, 1, 0, 0 };

void effectRotation(int startRow, int startCol, int size, int copy[][64]) {
	//È¸Àü
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			grid[startRow + j][startCol + size - 1 - i] = copy[startRow + i][startCol + j];
		}
	}
};

int getNearIce(int row, int col) {
	int count = 0;
	for (int i = 0; i < 4; i++) {
		int newRow = row + dy[i];
		int newCol = col + dx[i];

		if (newRow < 0 || newRow >= gridSize || newCol < 0 || newCol >= gridSize)
			continue;

		if (grid[newRow][newCol] == 0)
			continue;

		count++;
	}
	
	return count;
}

void effectFire() {
	vector<pair<int, int>> melt;
	for (int i = 0; i < gridSize; i++) {
		for (int j = 0; j < gridSize; j++) {
			if (grid[i][j] == 0)
				continue;

			if (getNearIce(i, j) >= 3)
				continue;

			melt.push_back(make_pair(i, j));
		}
	}

	for (int i = 0; i < melt.size(); i++) {
		pair<int, int> term = melt[i];
		grid[term.first][term.second]--;
	}
};

void firestorm(int L) {
	int clusterSize = int(pow(2, L));
	int copy[64][64];
	for (int i = 0; i < gridSize; i++) {
		for (int j = 0; j < gridSize; j++) {
			copy[i][j] = grid[i][j];
		}
	}

	for (int i = 0; i < gridSize; i += clusterSize) {
		for (int j = 0; j < gridSize; j += clusterSize) {
			effectRotation(i, j, clusterSize, copy);
		}
	}

	effectFire();
}

int getRemain() {
	int remain = 0;
	for (int i = 0; i < gridSize; i++) {
		for (int j = 0; j < gridSize; j++) {
			if (grid[i][j] == 0)
				continue;

			remain += grid[i][j];
		}
	}

	return remain;
}

void sizeDfs(int row, int col, int& size, bool check[][64]) {
	if (row < 0 || row >= gridSize || col < 0 || col >= gridSize)
		return;

	if (check[row][col] || grid[row][col] == 0)
		return;

	check[row][col] = true;
	size++;
	
	for (int i = 0; i < 4; i++) {
		int newRow = row + dy[i];
		int newCol = col + dx[i];
		sizeDfs(newRow, newCol, size, check);
	}
}

int getBig() {
	int max = 0;
	bool check[64][64];
	for (int i = 0; i < gridSize; i++) {
		for (int j = 0; j < gridSize; j++) {
			check[i][j] = false;
		}
	}

	for (int i = 0; i < gridSize; i++) {
		for (int j = 0; j < gridSize; j++) {
			if (check[i][j] || grid[i][j] == 0)
				continue;

			int size = 0;
			sizeDfs(i, j, size, check);
			max = max > size ? max : size;
		}
	}

	return max;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> Q;
	gridSize = int(pow(2, N));

	for (int i = 0; i < gridSize; i++) {
		for (int j = 0; j < gridSize; j++) {
			cin >> grid[i][j];
		}
	}

	for (int i = 0; i < Q; i++) {
		int L;
		cin >> L;
		firestorm(L);
	}

	cout << getRemain() << '\n' << getBig();
	return 0;
}