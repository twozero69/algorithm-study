#include <iostream>
#include <vector>
using namespace std;

int N;
int score = 0;
vector<bool> blueBoard[4];
vector<bool> greenBoard[4];

void insertOne(vector<bool>* board, int pos) {
	board[pos].push_back(true);
}

void insertTwice(vector<bool>* board, int pos) {
	for (int i = 0; i < 2; i++)
		board[pos].push_back(true);
}

void insertSync(vector<bool>* board, int pos1, int pos2) {
	int bigPos, smallPos;
	if (board[pos1].size() > board[pos2].size()) {
		bigPos = pos1;
		smallPos = pos2;
	}
	else {
		bigPos = pos2;
		smallPos = pos1;
	}

	int gap = board[bigPos].size() - board[smallPos].size();
	for (int i = 0; i < gap; i++) {
		board[smallPos].push_back(false);
	}

	board[pos1].push_back(true);
	board[pos2].push_back(true);
}

void insertBlock(int type, int row, int col) {
	switch (type) {
	case 1:
		insertOne(blueBoard, row);
		insertOne(greenBoard, col);
		break;
	case 2:
		insertTwice(blueBoard, row);
		insertSync(greenBoard, col, col + 1);
		break;
	case 3:
		insertSync(blueBoard, row, row + 1);
		insertTwice(greenBoard, col);
		break;
	}
}

void eraseLine(vector<bool>* board, int idx) {
	for (int i = 0; i < 4; i++) {
		//해당 라인 지우기
		board[i].erase(board[i].begin() + idx);
		
		//false넣어둔거 지우기
		while (true) {
			if (board[i].empty())
				break;

			if (board[i].back())
				break;

			board[i].pop_back();
		}
	}
}

void getScore(vector<bool>* board) {
	for (int i = 0; i < 4; i++) {
		bool flag = true;
		for (int j = 0; j < 4; j++) {
			if (board[j].size() <= i) {
				flag = false;
				break;
			}

			if (!board[j][i]) {
				flag = false;
				break;
			}
		}

		if (flag) {
			eraseLine(board, i);
			score++;
			i--;
		}
	}
}

bool updateLine(vector<bool>* board) {
	for (int i = 0; i < 4; i++) {
		if (board[i].size() < 5)
			continue;

		for (int j = 0; j < 4; j++) {
			if (board[j].size() == 0)
				continue;

			board[j].erase(board[j].begin());
		}

		return true;
	}

	return false;
}

int getBoardCnt() {
	int sum = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < blueBoard[i].size(); j++) {
			if (blueBoard[i][j])
				sum++;
		}

		for (int j = 0; j < greenBoard[i].size(); j++) {
			if (greenBoard[i][j])
				sum++;
		}
	}

	return sum;
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		int t, x, y;
		cin >> t >> x >> y;
		
		insertBlock(t, x, y);

		while (true) {
			getScore(blueBoard);
			if (!updateLine(blueBoard))
				break;

		}

		while (true) {
			getScore(greenBoard);
			if (!updateLine(greenBoard))
				break;
		}
	}

	cout << score << '\n' << getBoardCnt();
	return 0;
}