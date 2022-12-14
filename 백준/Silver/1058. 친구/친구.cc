#include <iostream>
using namespace std;

int N;//사람의 수
char arr[50][50];

int countFriends(int idx) {
	int _count = 0;
	bool check[50] = { false, false, false, };

	for (int i = 0; i < N; i++) {
		if (i == idx)
			continue;

		if (arr[idx][i] == 'Y') {//1 그냥 친구
			if (!check[i]) {
				_count++;
				check[i] = true;
			}
		}
		else {//2 친구의 친구
			for (int j = 0; j < N; j++) {
				if (arr[idx][j] == 'Y' && arr[i][j] == 'Y' && !check[i]) {
					_count++;
					check[i] = true;
					break;
				}
			}
		}
	}

	return _count;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
		}
	}

	int max = 0;
	for (int j = 0; j < N; j++) {
		int term = countFriends(j);
		max = max < term ? term : max;
	}

	cout << max;

	return 0;
}