#include <iostream>
#include <vector>
using namespace std;

typedef struct floor {
	int duration = 0;
	bool robot = false;
}FLOOR;

int N, K;
int N2;
FLOOR floors[200];
int step = 0;
int brokenFloor = 0;
int inIdx = 0;
vector<int> robot;

void setNewInIdx() {
	inIdx = (inIdx - 1 + N2) % N2;
};

int getNextIdx(int idx) { 
	return (idx + 1) % N2;
}

int getOutIdx() {
	return (inIdx + N - 1) % N2;
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> K;
	N2 = N * 2;
	for (int i = 0; i < N2; i++) {
		cin >> floors[i].duration;
	}

	while (brokenFloor < K) {
		//1. 벨트를 회전
		setNewInIdx();
		int outIdx = getOutIdx();
		if (!robot.empty()) {
			if (outIdx == robot[0]) {
				floors[robot[0]].robot = false;
				robot.erase(robot.begin());
			}
		}

		//2. 로봇이동, 내리기
		for (int i = 0; i < robot.size(); i++) {
			//로봇이동
			int nextIdx = getNextIdx(robot[i]);
			if (floors[nextIdx].duration == 0 || floors[nextIdx].robot)
				continue;

			floors[robot[i]].robot = false;
			floors[nextIdx].robot = true;
			robot[i] = nextIdx;

			//내구도감소
			floors[nextIdx].duration--;
			if (floors[nextIdx].duration == 0)
				brokenFloor++;

			//내리기
			if (nextIdx == outIdx) {
				floors[nextIdx].robot = false;
				robot.erase(robot.begin() + i);
				i--;
			}
		}

		//3. 로봇올리기
		if (floors[inIdx].duration > 0) {
			floors[inIdx].robot = true;
			robot.push_back(inIdx);
			floors[inIdx].duration--;
			if (floors[inIdx].duration == 0)
				brokenFloor++;
		}

		step++;
	}

	cout << step;
	return 0;
};