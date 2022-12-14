#include <iostream>
using namespace std;

typedef struct work {
	int T;
	int P;
}Work;

Work _work[15];
int N;
int result = 0;

//day 오늘의 날짜, workday 남은 근무기간, stack 지금까지의 이익저장
void dfs(int day, int workday, int stack) {
	if (day == N) {//1. 퇴사일이 되었다. 퇴사를 하자.
		result = result > stack ? result : stack;
		return;
	}
	
	if (workday == 0) {//2. 일손이 생겼다. 일을하자.
		if (_work[day].T == 1) { //1일 짜리 일의 경우 무조건 한다.
			dfs(day + 1, 0, stack + _work[day].P);
			return;
		}
		else {
			//퇴사전에 일을 끝낼 수 있는지 체크
			if (N - day < _work[day].T) {
				dfs(day + 1, 0, stack);
				return;
			}
			else {//일을 받는 경우와 넘기는 경우를 모두 발생시킨다.
				dfs(day + 1, 0, stack);
				dfs(day + 1, _work[day].T - 1, stack + _work[day].P);
			}
		}
	}
	else {//3. 일이 남았다. 열심히 일을 하자.
		dfs(day + 1, workday - 1, stack);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> _work[i].T >> _work[i].P;
	}

	dfs(0, 0, 0);
	cout << result;
	return 0;
}