#include <iostream>
#include <string.h>
using namespace std;

int N, M, K;
int _array[51][51];
int termarr[51][51];		//복사용
int r[6], c[6], s[6];
bool check[6];
int cycle[6];
int result= 2147483647;

void counting() {
	for (int i = 1; i <= N; i++) {
		int sum = 0;

		for (int j = 1; j <= M; j++) {
			sum += termarr[i][j];
		}
		
		result = result > sum ? sum : result;
	}
}

void swap(int& a, int& b) {
	int term;
	term = a;
	a = b;
	b = term;
}

void cane(int opn) {
	for (int size = 1; size <= s[opn]; size++) {
		for (int a = c[opn] + size; a > c[opn] - size; a--) {//1. 행은 r-size로 고정 왼쪽으로 토스-오른쪽으로 밀음
			swap(termarr[r[opn] - size][a], termarr[r[opn] - size][a - 1]);
		}

		for (int i = r[opn] - size; i < r[opn] + size; i++) {//2. 열은 c-size로 고정 아래로 토스-위로 밀음
			swap(termarr[i][c[opn] - size], termarr[i + 1][c[opn] - size]);
		}

		for (int b = c[opn] - size; b < c[opn] + size; b++) {//3. 행은 r+size로 고정 오른쪽으로 토스-왼쪽으로 밀음
			swap(termarr[r[opn] + size][b], termarr[r[opn] + size][b + 1]);
		}

		for (int j = r[opn] + size; j > r[opn] - size + 1; j--) {//4. 열은 c+size로 고정 위로 토스-아래로밀음, 다른 애들보다 1회 swap 덜해야함
			swap(termarr[j][c[opn] + size], termarr[j - 1][c[opn] + size]);
		}
	}
}

void operation() {
	memcpy(termarr, _array, sizeof(int) * 51 * 51);

	for (int j = 0; j < K; j++) {
		cane(cycle[j]);
	}
}

void dfs(int count) {
	if (count == K) {
		operation();
		counting();
		return;
	}

	for (int i = 0; i < K; i++) {
		if (!check[i]) {
			cycle[count] = i;
			check[i] = true;
			dfs(count + 1);

			check[i] = false;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M >> K;

	int term;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> term;
			_array[i][j] = term;
		}
	}

	for (int k = 0; k < K; k++) {
		cin >> r[k] >> c[k] >> s[k];
	}

	dfs(0);

	cout << result;
}