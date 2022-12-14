#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int __array[51][10];
int _size;
int result;
int check[10];
int cycle_real[9];

void play_game() {
	int _score = 0;
	int count = 0;
	for (int i = 1; i <= _size; i++) {
		int ground[3] = { 0 };		//0: 1루, 1: 2루, 2: 3루
		int out = 0;
		while (out < 3) {
			switch (__array[i][cycle_real[count]]) {
			case 0:
				out++;
				break;
			case 1:
				if (ground[2]) {
					_score++;
					ground[2] = 0;
				}
				
				if (ground[1]) {
					ground[2] = 1;
					ground[1] = 0;
				}

				if (ground[0]) {
					ground[1] = 1;
				}

				ground[0] = 1;

				break;
			case 2:
				if (ground[2]) {
					_score++;
					ground[2] = 0;
				}

				if (ground[1]) {
					_score++;
				}

				if (ground[0]) {
					ground[2] = 1;
					ground[0] = 0;
				}

				ground[1] = 1;

				break;
			case 3:
				if (ground[2]) {
					_score++;
				}

				if (ground[1]) {
					_score++;
					ground[1] = 0;
				}

				if (ground[0]) {
					_score++;
					ground[0] = 0;
				}

				ground[2] = 1;

				break;
			case 4:
				if (ground[2]) {
					_score++;
					ground[2] = 0;
				}

				if (ground[1]) {
					_score++;
					ground[1] = 0;
				}

				if (ground[0]) {
					_score++;
					ground[0] = 0;
				}

				_score++;

				break;
			}

			count = (count + 1) % 9;
		}
	}

	result = max(result, _score);
}

void detectgame(int count) {
	if (count>8) {
		play_game();
		return;
	}
	else if (count == 3) {
		detectgame(count + 1);
		return;
	}
	

	for (int i = 2; i <= 9; i++) {
		if (check[i] == 0) {
			cycle_real[count] = i;
			check[i] = 1;
			detectgame(count + 1);
			check[i] = 0;
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cout.tie(0);
	cin.tie(0);

	cin >> _size;
	int term;
	for (int i = 1; i <= _size; i++) {
		for (int j = 1; j <= 9; j++) {
			cin >> term;
			__array[i][j] = term;
		}
	}
	
	cycle_real[3] = 1;
	check[1] = 1;
	detectgame(0);

	cout << result;
}