#include <iostream>
using namespace std;

#define subStarty 0 
int N;
char _data[3072][6143];

void setStar(int numy, int startx) {
	if (numy == 3) {
		_data[0][startx + 2] = '*';
		_data[1][startx + 1] = _data[1][startx + 3] = '*';
		_data[2][startx] = _data[2][startx + 1] = _data[2][startx + 2] = _data[2][startx + 3] = _data[2][startx + 4] = '*';
		return;
	}

	int subNumy = numy / 2;
	int subStartx = startx + subNumy;
	setStar(subNumy, subStartx);
	
	int copyNumx = numy - 1;
	int copyNumy = subNumy;
	int copyStarty = numy / 2;
	int copyStartx1 = startx;
	int copyStartx2 = startx + numy;

	for (int i = 0; i < copyNumy; i++) {
		for (int j = 0; j < copyNumx; j++) {
			_data[copyStarty + i][copyStartx1 + j] = _data[copyStarty + i][copyStartx2 + j] = _data[subStarty + i][subStartx + j];
		}
	}
}

void printStar(int height) {
	int width = 2 * height - 1;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (_data[i][j] == '*')
				cout << '*';
			else
				cout << ' ';
		}
		cout << '\n';
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	setStar(N, 0);
	printStar(N);
	return 0;
}