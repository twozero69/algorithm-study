#include <iostream>
#include <math.h>
using namespace std;


int K;
int gears[4][8];
int left_idx[4] = { 6,6,6,6 };


void move_gear(int gear_idx, int flag_LR, int dir) {
	//1. 기어번호 체크
	if (0 > gear_idx || gear_idx >= 4)
		return;

	//2. NS접합이 되는지 체크
	switch (flag_LR) {	//0-left방향으로 진행중, 1-right방향으로 진행중, 2-최초기어
		case 0: {
			int parent_gear_idx = gear_idx + 1;
			int my_right_idx = (left_idx[gear_idx] + 4) % 8;
			int parent_left_idx = left_idx[parent_gear_idx];
			if (gears[gear_idx][my_right_idx] == gears[parent_gear_idx][parent_left_idx])
				return;
			break;
		}
		case 1: {
			int parent_gear_idx = gear_idx - 1;
			int my_left_idx = left_idx[gear_idx];
			int parent_right_idx = (left_idx[parent_gear_idx] + 4) % 8;
			if (gears[gear_idx][my_left_idx] == gears[parent_gear_idx][parent_right_idx])
				return;
			break;
		}
	}

	//3. 진행방향에 따라 재귀호출
	switch (flag_LR) {	//0-left방향으로 진행중, 1-right방향으로 진행중, 2-최초기어
	case 0:
		move_gear(gear_idx - 1, 0, -dir);
		break;
	case 1:
		move_gear(gear_idx + 1, 1, -dir);
		break;
	case 2:
		move_gear(gear_idx - 1, 0, -dir);
		move_gear(gear_idx + 1, 1, -dir);
		break;
	}

	//4. 회전방향에 따라서 기어회전
	left_idx[gear_idx] = (left_idx[gear_idx] - dir + 8) % 8;
}


void result() {
	int sum = 0;
	for (int i = 0; i < 4; i++) {
		int up_idx = (left_idx[i] + 2) % 8;
		if (gears[i][up_idx] == 1)
			sum += pow(2, i);
	}

	cout << sum;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	char term;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			cin >> term;
			gears[i][j] = term - 48;
		}
	}

	cin >> K;
	int gear_no, dir;
	for (int i = 0; i < K; i++) {
		cin >> gear_no >> dir;
		move_gear(gear_no - 1, 2, dir);
	}

	result();
	return 0;
}