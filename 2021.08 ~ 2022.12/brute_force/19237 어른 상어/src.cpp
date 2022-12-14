#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef struct smell {
	int sharqNo = 0;
	int sec = 0;
}SMELL;

typedef struct shell {
	int sharqNo = 0;
	vector<int> otherSharq;
	vector<SMELL> smells;
}SHELL;

int N, M, K;
int priorityDir[401][5][5];
int sharqDir[401];
SHELL shells[21][21];
int runtime = 0;
int dy[5] = { 0, -1, 1, 0, 0 };
int dx[5] = { 0, 0, 0, -1, 1 };

void smellSharqs() {
	//상어가 있는 칸에 냄새를 뿌리기
	for (int row = 1; row <= N; row++) {
		for (int col = 1; col <= N; col++) {
			int no = shells[row][col].sharqNo;
			if (no == 0)
				continue;

			SMELL term;
			term.sharqNo = no;
			term.sec = K;
			shells[row][col].smells.push_back(term);
		}
	}
}

void moveSharq(int row, int col) {
	int no = shells[row][col].sharqNo;
	if (no == 0)
		return;

	//4개의 방향을 탐색 - 먼저 냄새가 없는 칸의 방향을 탐색
	for (int i = 1; i <= 4; i++) {
		int currentDir = sharqDir[no];
		int nextDir = priorityDir[no][currentDir][i];
		int nextRow = row + dy[nextDir];
		int nextCol = col + dx[nextDir];

		//범위체크
		if (nextRow<1 || nextRow>N || nextCol<1 || nextCol>N)
			continue;

		vector<SMELL> nextSmells = shells[nextRow][nextCol].smells;

		//냄새가 없는 칸인지 확인
		if (!nextSmells.empty())
			continue;

		//상어를 이동
		sharqDir[no] = nextDir;
		shells[row][col].sharqNo = 0;
		shells[nextRow][nextCol].otherSharq.push_back(no);
		return;
	}

	//4개의 방향을 탐색 - 자신의 냄새가 있는 방향을 탐색
	for (int i = 1; i <= 4; i++) {
		int currentDir = sharqDir[no];
		int nextDir = priorityDir[no][currentDir][i];
		int nextRow = row + dy[nextDir];
		int nextCol = col + dx[nextDir];

		//범위체크
		if (nextRow<1 || nextRow>N || nextCol<1 || nextCol>N)
			continue;

		//자신의 냄새가 있는지 체크
		int nextNo = shells[nextRow][nextCol].sharqNo;
		vector<SMELL> nextSmells = shells[nextRow][nextCol].smells;
		for (int j = 0; j < nextSmells.size(); j++) {
			if (nextSmells[j].sharqNo != no)
				continue;

			//상어를 이동
			sharqDir[no] = nextDir;
			shells[row][col].sharqNo = 0;
			shells[nextRow][nextCol].otherSharq.push_back(no);
			return;
		}
	}
}

void moveSharqs() {
	//상어를 이동
	for (int row = 1; row <= N; row++) {
		for (int col = 1; col <= N; col++) {
			moveSharq(row, col);
		}
	}
}

void eraseSharqs() {
	for (int row = 1; row <= N; row++) {
		for (int col = 1; col <= N; col++) {
			int no = shells[row][col].sharqNo;
			vector<int> sharqs = shells[row][col].otherSharq;

			if (no != 0)
				sharqs.push_back(no);

			sort(sharqs.begin(), sharqs.end());
			if (sharqs.empty()) {
				shells[row][col].sharqNo = 0;
			}
			else {
				M -= (sharqs.size() - 1);
				shells[row][col].sharqNo = sharqs.front();
			}

			shells[row][col].otherSharq.clear();
		}
	}
}

void eraseSmells() {
	for (int row = 1; row <= N; row++) {
		for (int col = 1; col <= N; col++) {
			for (int i = 0; i < shells[row][col].smells.size(); i++) {
				shells[row][col].smells[i].sec--;
				if (shells[row][col].smells[i].sec != 0)
					continue;

				shells[row][col].smells.erase(shells[row][col].smells.begin() + i);
				i--;
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> shells[i][j].sharqNo;
		}
	}

	for (int i = 1; i <= M; i++) {
		cin >> sharqDir[i];
	}

	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= 4; j++) {
			for (int k = 1; k <= 4; k++) {
				cin >> priorityDir[i][j][k];
			}
		}
	}

	while (true) {
		//상어가 1마리만 남아서 종료
		if (M == 1) {
			cout << runtime;
			return 0;
		}

		//1000초가 지나서 종료
		if (runtime >= 1000) {
			cout << -1;
			return 0;
		}

		//상어 냄새 퍼뜨리기
		smellSharqs();

		//상어 움직이기
		moveSharqs();

		//같은칸에 있는 상어 내쫓기
		eraseSharqs();

		//냄새 지우기
		eraseSmells();

		runtime++;
	}

	return 0;
}