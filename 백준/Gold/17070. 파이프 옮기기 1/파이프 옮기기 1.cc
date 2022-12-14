#include <iostream>
using namespace std;

int _size;
int __array[17][17];
int result;

void dfs(int x, int y, int pose) {		//pose 1은 가로 2는 세로 3은 대각선
	if (x == _size && y == _size) {
		if (__array[x][y] == 1)
			return;
		if (pose == 3 && (__array[x - 1][y] == 1 || __array[x][y - 1] == 1)) 
			return;
		result++;
		return;
	}

	if (x > _size || y > _size) {
		return;
	}

	if (__array[x][y] == 1) {
		return;
	}

	switch (pose) {
	case 1:
		dfs(x, y + 1, 1);
		dfs(x + 1, y + 1, 3);
		break;
	case 2:
		dfs(x + 1, y, 2);
		dfs(x + 1, y + 1, 3);
		break;
	case 3:
		if (__array[x - 1][y] == 1 || __array[x][y - 1] == 1) {
			return;
		}
		dfs(x, y + 1, 1);
		dfs(x + 1, y, 2);
		dfs(x + 1, y + 1, 3);
		break;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> _size;

	int term;
	for (int i = 1; i <= _size; i++) {
		for (int j = 1; j <= _size; j++) {
			cin >> term;
			__array[i][j] = term;
		}
	}

	dfs(1, 2, 1);

	cout << result;
}