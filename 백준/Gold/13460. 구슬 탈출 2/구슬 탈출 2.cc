#include <iostream>
using namespace std;

int result = 11;
int N, M;
char board[10][10];
int count_ = 0;
pair<int, int> red;
pair<int, int> blue;
pair<int, int> hole;
int dy[4] = { -1,1,0,0 };	//0상, 1하, 2좌, 3우
int dx[4] = { 0,0,-1,1 };
bool status = true;

bool movered(int direction) {
	while (true) {
		int newy = red.first + dy[direction];
		int newx = red.second + dx[direction];

		if (blue.first == newy && blue.second == newx)
			return false;
		
		switch (board[newy][newx]) {
		case '.':
			red.first = newy;
			red.second = newx;
			break;
		case '#':
			return false;
			break;
		case  'O':
			red.first = -1;
			red.second = -1;
			return true;
			break;
		}
	}
}

bool moveblue(int direction) {
	while (true) {
		int newy = blue.first + dy[direction];
		int newx = blue.second + dx[direction];

		if (red.first == newy && red.second == newx)
			return false;

		switch (board[newy][newx]) {
		case '.':
			blue.first = newy;
			blue.second = newx;
			break;
		case '#':
			return false;
			break;
		case  'O':
			blue.first = -2;
			blue.second = -2;
			return true;
			break;
		}
	}
}

void marble(int direction, bool redfirst) {
	bool redflag, blueflag;
	if (redfirst) {
		redflag=movered(direction);
		blueflag=moveblue(direction);
	}
	else {
		blueflag = moveblue(direction);
		redflag = movered(direction);
	}

	if (redflag||blueflag) {
		status = false;

		if (redflag && !blueflag)
			result = result < count_ ? result : count_;
	}
}

void move(int direction) {
	switch (direction) {
	case 0://상
		if (red.first < blue.first)
			marble(direction, true);
		else
			marble(direction, false);
		break;
	case 1://하
		if (red.first > blue.first)
			marble(direction, true);
		else
			marble(direction, false);
		break;
	case 2://좌
		if (red.second < blue.second)
			marble(direction, true);
		else
			marble(direction, false);
		break;
	case 3://우
		if (red.second > blue.second)
			marble(direction, true);
		else
			marble(direction, false);
		break;
	}
}

void dfs() {	//0상, 1하, 2좌, 3우
	if (count_ == 10)
		return;

	pair<int, int> red_origin = red;
	pair<int, int> blue_origin = blue;
	for (int i = 0; i < 4; i++) {
		count_++;
		move(i);	//움직였는데 구슬이 구멍에 하나라도 빠지면 이 경로에 대해서는 탐색을 그만둬야 함.
		if (!status) {
			red = red_origin;
			blue = blue_origin;
			status = true;
			count_--;
			continue;
		}
		dfs();
		count_--;
		red = red_origin;
		blue = blue_origin;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
			switch (board[i][j]) {
			case 'O':
				hole.first = i;
				hole.second = j;
				break;
			case 'R':
				red.first = i;
				red.second = j;
				board[i][j] = '.';
				break;
			case 'B':
				blue.first = i;
				blue.second = j;
				board[i][j] = '.';
				break;
			}
		}
	}

	dfs();
	if (result == 11)
		cout << "-1";
	else
		cout << result;

	return 0;
}