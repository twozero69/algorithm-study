#include <iostream>
#include <queue>
using namespace std;

int N, K, L;	//N보드의 크기, K사과의 개수, L방향전환의 횟수
int board[101][101];	//사과의 위치와 뱀의 몸을 기록, 0-빈칸, 1-사과, 2-뱀
queue<pair<int, char>> dirRecord;	//방향전환내역을 기록 first-방향전환 시간, second-전환 방향
int dy[4] = { 0,-1,0,1 };	//0-좌,1-상,2-우,3-하
int dx[4] = { -1,0,1,0 };
int dir;	//지렁이의 진행방향을 저장, 최초는 오른쪽
queue<pair<int, int>> body;	//뱀의 몸을 기록 뱀의 꼬리를 쉽게 파악하기 위함
int time_;	//게임의 진행시간을 기록
bool gameflag;	//게임의 상태를 기록

void snake_game() {
	gameflag = true;
	board[1][1] = 2;
	body.push(make_pair(1, 1));
	dir = 2;
	time_ = 0;
	pair<int, int> head(make_pair(1, 1));
	while (gameflag) {
		//방향전환체크
		if (!dirRecord.empty()) {
			if (time_ == dirRecord.front().first) {
				switch (dirRecord.front().second) {
				case 'L':
					dir = (dir + 3) % 4;
					break;
				case 'D':
					dir = (dir + 1) % 4;
					break;
				}

				dirRecord.pop();
			}
		}
		
		//뱀이동
		head.first += dy[dir];
		head.second += dx[dir];
		body.push(head);
		time_++;

		//벽과 충돌체크
		if (head.first<1 || head.first>N || head.second<1 || head.second>N)
			break;

		//사과체크, 뱀의 몸 충돌체크
		switch (board[head.first][head.second]) {
		case 0:	//이동한 곳이 빈공간인 경우
			board[head.first][head.second] = 2;
			board[body.front().first][body.front().second] = 0;
			body.pop();
			break;
		case 1:	//이공한 곳에 사과가 있을 경우
			board[head.first][head.second] = 2;
			break;
		case 2:	//이동한 곳이 자신의 몸일 경우
			gameflag = false;
			break;
		}
	}

	cout << time_;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> K;
	int row, col;
	for (int i = 0; i < K; i++) {
		cin >> row >> col;
		board[row][col] = 1;	//사과의 위치를 기록
	}

	cin >> L;
	int time;
	char direction;
	for (int i = 0; i < L; i++) {
		cin >> time >> direction;
		dirRecord.push(make_pair(time, direction));
	}

	snake_game();
	return 0;
}