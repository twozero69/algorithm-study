#include <iostream>
#include <vector>
using namespace std;

int arr[9][9];
vector<pair<int, int>> zeros;
bool check[9][9][10];	//false가 가능한 상태, true가 불가능한 상태
bool flag = false;

void fillCheck(int row, int col, int num) {
	//행처리
	for (int i = 0; i < 9; i++) {
		check[row][i][num] = true;
	}

	//열처리
	for (int i = 0; i < 9; i++) {
		check[i][col][num] = true;
	}

	//3x3처리
	int yidx = row / 3;
	int xidx = col / 3;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			check[3 * yidx + i][3 * xidx + j][num] = true;
		}
	}
}

void fillCheck2(int row, int col, int num, vector<pair<int, int>>& backData) {
	//행처리
	for (int i = 0; i < 9; i++) {
		if (!check[row][i][num]) {
			check[row][i][num] = true;
			backData.push_back(make_pair(row, i));
		}
	}

	//열처리
	for (int i = 0; i < 9; i++) {
		if (!check[i][col][num]) {
			check[i][col][num] = true;
			backData.push_back(make_pair(i, col));
		}
	}

	//3x3처리
	int yidx = row / 3;
	int xidx = col / 3;
	for (int i = 0; i < 3; i++) {
		int y = 3 * yidx + i;
		for (int j = 0; j < 3; j++) {
			int x = 3 * xidx + j;
			if (!check[y][x][num]) {
				check[y][x][num] = true;
				backData.push_back(make_pair(y, x));
			}
		}
	}
}

void checking() {
	//행체크
	for (int i = 0; i < 9; i++) {
		bool rowCheck[10] = { false, };
		for (int j = 0; j < 9; j++) {
			if (rowCheck[arr[i][j]])
				return;

			rowCheck[arr[i][j]] = true;
		}
	}

	//열체크
	for (int i = 0; i < 9; i++) {
		bool colCheck[10] = { false, };
		for (int j = 0; j < 9; j++) {
			if (colCheck[arr[j][i]])
				return;

			colCheck[arr[j][i]] = true;
		}
	}

	//3x3체크
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			bool x3Check[10] = { false, };
			int ystart = i * 3;
			int xstart = j * 3;
			for (int a = 0; a < 3; a++) {
				for (int b = 0; b < 3; b++) {
					if (x3Check[arr[ystart + a][xstart + b]])
						return;

					x3Check[arr[ystart + a][xstart + b]] = true;
				}
			}
		}
	}

	flag = true;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cout << arr[i][j] << ' ';
		}
		cout << '\n';
	}
}

void dfs(int idx) {
	if (flag)
		return;

	if (idx == zeros.size()) {
		checking();
		return;
	}

	int y = zeros[idx].first;
	int x = zeros[idx].second;
	for (int i = 1; i < 10; i++) {
		if (check[y][x][i])
			continue;
		
		vector<pair<int, int>> back;
		arr[y][x] = i;
		fillCheck2(y, x, i, back);
		dfs(idx + 1);
		arr[y][x] = 0;
		for (int j = 0; j < back.size(); j++)
			check[back[j].first][back[j].second][i] = false;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 0)
				zeros.push_back(make_pair(i, j));
			else
				fillCheck(i, j, arr[i][j]);
		}
	}

	dfs(0);
	return 0;
}