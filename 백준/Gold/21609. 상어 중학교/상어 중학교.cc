#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;


typedef struct blockGroup {
	int size = 0;
	int rainbowNum = 0;
	int row;
	int col;
}BLOCKGROUP;

int N, M;
int map[20][20];
int result = 0;
int dx[4] = { 0, 0, -1, 1 };
int dy[4] = { 1, -1, 0, 0 };
stack<pair<int, int>> rainbowReset;

void effectRotation() {
	int copy[20][20];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			copy[i][j] = map[i][j];
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			map[N - j - 1][i] = copy[i][j];
		}
	}
}

void effectGravity2Cell(int row, int col) {
	int newRow = row;
	for (int i = row + 1; i < N; i++) {
		if (map[i][col] != -2)
			break;

		newRow = i;
	}

	int term = map[row][col];
	map[row][col] = -2;
	map[newRow][col] = term;
};

void effectGravity() {
	for (int i = N - 1; i >= 0; i--) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] >= 0)
				effectGravity2Cell(i, j);
		}
	}
};

void dfs(int row, int col, int color, bool check[][20], BLOCKGROUP& term) {
	if (row < 0 || row >= N || col < 0 || col >= N)
		return;

	if (check[row][col])
		return;

	int myColor = map[row][col];
	if (myColor != color && myColor != 0)
		return;

	check[row][col] = true;
	term.size++;
	if (myColor == 0)
		term.rainbowNum++;

	for (int i = 0; i < 4; i++) {
		dfs(row + dy[i], col + dx[i], color, check, term);
	}

	if (myColor == 0)
		rainbowReset.push(make_pair(row, col));
}

bool compare(BLOCKGROUP A, BLOCKGROUP B) {
	if (A.size != B.size)
		return A.size > B.size;

	if (A.rainbowNum != B.rainbowNum)
		return A.rainbowNum > B.rainbowNum;

	if (A.row != B.row)
		return A.row > B.row;

	return A.col > B.col;
}

BLOCKGROUP searchBigGroup() {
	vector<BLOCKGROUP> blockGroups;
	bool check[20][20];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			check[i][j] = false;
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] >= 1 && !check[i][j]) {
				BLOCKGROUP term;
				term.row = i;
				term.col = j;
				dfs(i, j, map[i][j], check, term);
				if (term.size >= 2)
					blockGroups.push_back(term);

				while (!rainbowReset.empty()) {
					pair<int, int> rainbow = rainbowReset.top();
					rainbowReset.pop();
					check[rainbow.first][rainbow.second] = false;
				}
			}
		}
	}

	if (blockGroups.empty()) {
		BLOCKGROUP term;
		return term;
	}

	sort(blockGroups.begin(), blockGroups.end(), compare);
	return blockGroups[0];
}

void eraseDfs(int row, int col, int color) {
	if (row < 0 || row >= N || col < 0 || col >= N) 
		return;

	if (map[row][col] == -2)
		return;

	int myColor = map[row][col];
	if (myColor != color && myColor != 0)
		return;

	map[row][col] = -2;
	
	for (int i = 0; i < 4; i++) {
		eraseDfs(row + dy[i], col + dx[i], color);
	}
}

void eraseBlockGroup(BLOCKGROUP blockGroup) {
	eraseDfs(blockGroup.row, blockGroup.col, map[blockGroup.row][blockGroup.col]);
}

void printMap() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << map[i][j] << ' ';
		}
		cout << '\n';
	}
	cout << result << '\n';
}

bool playgame() {
	BLOCKGROUP bigGroup = searchBigGroup();
	if (bigGroup.size == 0)
		return false;

	eraseBlockGroup(bigGroup);
	result += bigGroup.size * bigGroup.size;

	effectGravity();
	effectRotation();
	effectGravity();

	return true;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	while (true) {
		if (!playgame())
			break;
	}

	cout << result;
	return 0;
}