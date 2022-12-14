#include <iostream>
using namespace std;

int N, M;
int x, y;	//x가 세로 y가 가로
int K;

int map[20][20];
int dx[4] = { 0,0,-1,1 };	//0-동, 1-서, 2-북, 3-남
int dy[4] = { 1,-1,0,0 };
int dice[6] = { 0, };
/*
초기상태

인덱스
  0
1 2 3
  4
  5       

 회전하면서 값은 계속 변하지만 인덱스 2가 윗면, 인덱스 5가 밑면임.
*/


/*다음 이동이 유효한지 확인하는 함수*/
bool checkNext(int dir) {
	//y가 가로 x가 세로
	int nexty = y + dy[dir];
	int nextx = x + dx[dir];

	if (nexty < 0 || nexty >= M || nextx < 0 || nextx >= N)
		return false;

	y = nexty;
	x = nextx;
	return true;
}

//주사위의 눈을 재배치하는 함수
void moveDice(int dir) {
	int term[6];
	for (int i = 0; i < 6; i++)
		term[i] = dice[i];

	switch (dir) {
	case 0:	//동쪽으로 굴림(인덱스 0, 4 안움직임)
		dice[1] = term[5];
		dice[2] = term[1];
		dice[3] = term[2];
		dice[5] = term[3];
		break;
	case 1:	//서쪽으로 굴림(인덱스 0, 4 안움직임)
		dice[1] = term[2];
		dice[2] = term[3];
		dice[3] = term[5];
		dice[5] = term[1];
		break;
	case 2:	//북쪽으로 굴림(인덱스 1, 3 안움직임)
		dice[0] = term[2];
		dice[2] = term[4];
		dice[4] = term[5];
		dice[5] = term[0];
		break;
	case 3:	//남쪽으로 굴림(인덱스 1, 3 안움직임)
		dice[0] = term[5];
		dice[2] = term[0];
		dice[4] = term[2];
		dice[5] = term[4];
		break;
	}
}

/*
눈을 새로 읽을지 판단하고 출력하는 함수
*/
void printDice() {
	//주사위 윗면출력
	cout << dice[2] << '\n';

	//새로운 주사위 눈을 읽을지 판단
	if (map[x][y] == 0) {
		map[x][y] = dice[5];
	}
	else {
		dice[5] = map[x][y];
		map[x][y] = 0;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	cin >> x >> y;
	cin >> K;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
		}
	}

	int dir;
	for (int i = 0; i < K; i++) {
		cin >> dir;
		if (!checkNext(dir-1))
			continue;
		
		moveDice(dir - 1);
		printDice();
	}

	return 0;
}