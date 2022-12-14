#include <iostream>
using namespace std;

int N = 0;
int result = 0;

typedef struct term {
	int col;
	int x1;	//기울기 -1에서의 x절편
	int x2;	//기울기 1에서의 x절편
}Term;

Term arr[15];

void dfs(int count) {
	if (count == N) {
		result++;
		return;
	}

	//유효영역에 퀸놓기
	for (int i = 0; i < N ; i++) {
		bool flag = true;
		for (int j = 0; j < count; j++) {
			if (arr[j].col == i) {
				flag = false;
				break;
			}

			if (count + i == arr[j].x1) {
				flag = false;
				break;
			}

			if (i - count == arr[j].x2) {
				flag = false;
				break;
			}
		}

		if (flag) {
			arr[count].col = i;
			arr[count].x1 = count + i;
			arr[count].x2 = i - count;
			dfs(count + 1);
		}
	}
}

int main() {
	cin >> N;
	dfs(0);
	cout << result;

	return 0;
}