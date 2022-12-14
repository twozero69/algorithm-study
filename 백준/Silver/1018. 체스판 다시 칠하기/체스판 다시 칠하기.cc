#include <iostream>
using namespace std;

int M, N;
char arr[50][50];
int result = 2147483647;

char chessTable1[8][8] = {
	{'W','B','W','B','W','B','W','B'},
	{'B','W','B','W','B','W','B','W'},
	{'W','B','W','B','W','B','W','B'},
	{'B','W','B','W','B','W','B','W'},
	{'W','B','W','B','W','B','W','B'},
	{'B','W','B','W','B','W','B','W'},
	{'W','B','W','B','W','B','W','B'},
	{'B','W','B','W','B','W','B','W'}
};

char chessTable2[8][8] = {
	{'B','W','B','W','B','W','B','W'},
	{'W','B','W','B','W','B','W','B'},
	{'B','W','B','W','B','W','B','W'},
	{'W','B','W','B','W','B','W','B'},
	{'B','W','B','W','B','W','B','W'},
	{'W','B','W','B','W','B','W','B'},
	{'B','W','B','W','B','W','B','W'},
	{'W','B','W','B','W','B','W','B'},
};

void checking(int starty, int startx) {
	int term1 = 0;
	int term2 = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (arr[starty + i][startx + j] != chessTable1[i][j])
				term1++;
			if (arr[starty + i][startx + j] != chessTable2[i][j])
				term2++;
		}
	}

	result = result < term1 ? result : term1;
	result = result < term2 ? result : term2;
}

int main() {
	cin >> M >> N;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
		}
	}

	int endy = M - 8;
	int endx = N - 8;
	for (int i = 0; i <= endy; i++) {
		for (int j = 0; j <= endx; j++) {
			checking(i, j);
		}
	}

	cout << result;
	return 0;
}