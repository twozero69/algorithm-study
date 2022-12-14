#include <iostream>
using namespace std;

int N, M;	//N행 M열
int A[50][50];
int B[50][50];

int main() {
	cin >> N >> M;

	//A
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			char term;
			cin >> term;
			A[i][j] = (int)term - 48;
		}
	}

	//B
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			char term;
			cin >> term;
			B[i][j] = (int)term - 48;
		}
	}

	//처리
	//A->B
	int _count = 0;
	for (int i = 0; i < N - 2; i++) {
		for (int j = 0; j < M - 2; j++) {
			if (A[i][j] != B[i][j]) {
				_count++;
				for (int a = 0; a < 3; a++) {
					for (int b = 0; b < 3; b++) {
						int newy = i + a;
						int newx = j + b;

						A[newy][newx] = (A[newy][newx] + 1) % 2;
					}
				}
			}
		}
	}

	//A==B확인
	bool flag = true;
	for (int i = 0; i < N; i++) {
		if (!flag)
			break;

		for (int j = 0; j < M; j++) {
			if (A[i][j] != B[i][j]) {
				flag = false;
				break;
			}
		}
	}

	int result = flag ? _count : -1;
	cout << result;
	return 0;
}