#include <iostream>
#include <math.h>
using namespace std;
#define INT_MAX 2147483647


int N;
int arr[20][20];
bool check[20];
int result=INT_MAX;

int checking() {
	int term = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (check[i] == check[j]) {
				if (check[i])
					term += arr[i][j];
				else
					term -= arr[i][j];
			}
		}
	}

	return abs(term);
}

void dfs(int cnt, int idx) {
	if (cnt == N / 2) {
		int term = checking();
		result = result < term ? result : term;
		return;
	}

	if (N - idx > N / 2 - cnt)	//20-9 > 10 - 0 이건 들어감 , 20-10 > 10 - 0 이건 안들어감
		dfs(cnt, idx + 1);

	if (N - idx >= N / 2 - cnt) {
		check[idx] = true;
		dfs(cnt + 1, idx + 1);
		check[idx] = false;
	}
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
		}
	}

	dfs(0, 0);
	
	cout << result;
	return 0;
}