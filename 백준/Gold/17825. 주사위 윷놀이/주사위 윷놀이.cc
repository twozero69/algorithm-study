#include <iostream>
using namespace std;

typedef struct node {
	int value;
	int redNext;
	int blueNext = -1;
	bool mal = false;
}NODE;

//map의 mal과 malPos[4]는 백트랙킹 대상
NODE map[33];
int malPos[4] = { 0, 0, 0, 0 };

int dice[10];
int goalIdx = 32;
int result = 0;

void init() {
	map[0].value = 0;
	map[0].redNext = 1;

	map[1].value = 2;
	map[1].redNext = 2;

	map[2].value = 4;
	map[2].redNext = 3;

	map[3].value = 6;
	map[3].redNext = 4;

	map[4].value = 8;
	map[4].redNext = 5;

	map[5].value = 10;
	map[5].redNext = 6;
	map[5].blueNext = 21;

	map[6].value = 12;
	map[6].redNext = 7;

	map[7].value = 14;
	map[7].redNext = 8;

	map[8].value = 16;
	map[8].redNext = 9;

	map[9].value = 18;
	map[9].redNext = 10;

	map[10].value = 20;
	map[10].redNext = 11;
	map[10].blueNext = 25;

	map[11].value = 22;
	map[11].redNext = 12;

	map[12].value = 24;
	map[12].redNext = 13;

	map[13].value = 26;
	map[13].redNext = 14;

	map[14].value = 28;
	map[14].redNext = 15;

	map[15].value = 30;
	map[15].redNext = 16;
	map[15].blueNext = 27;
	
	map[16].value = 32;
	map[16].redNext = 17;

	map[17].value = 34;
	map[17].redNext = 18;

	map[18].value = 36;
	map[18].redNext = 19;

	map[19].value = 38;
	map[19].redNext = 20;

	map[20].value = 40;
	map[20].redNext = 32;

	map[21].value = 13;
	map[21].redNext = 22;

	map[22].value = 16;
	map[22].redNext = 23;

	map[23].value = 19;
	map[23].redNext = 24;

	map[24].value = 25;
	map[24].redNext = 30;
	
	map[25].value = 22;
	map[25].redNext = 26;

	map[26].value = 24;
	map[26].redNext = 24;
	
	map[27].value = 28;
	map[27].redNext = 28;

	map[28].value = 27;
	map[28].redNext = 29;

	map[29].value = 26;
	map[29].redNext = 24;
	
	map[30].value = 30;
	map[30].redNext = 31;

	map[31].value = 35;
	map[31].redNext = 20;

	map[32].value = 0;
	map[32].redNext = 32;
}

void dfs(int diceIdx, int sum) {
	if (diceIdx == 10) {
		result = result > sum ? result : sum;
		return;
	}

	int diceNum = dice[diceIdx];

	//말선택
	for (int i = 0; i < 4; i++) {
		int currentPos = malPos[i];
		//이미 도착한 말은 건너뛰기
		if (currentPos == goalIdx)
			continue;

		//주사위 눈 수만큼 이동
		int nextPos = currentPos;
		for (int j = 0; j < diceNum; j++) {
			if (j == 0 && map[nextPos].blueNext != -1) {
				nextPos = map[nextPos].blueNext;
				continue;
			}

			nextPos = map[nextPos].redNext;
		}

		//이미 말이 있는 칸이면 건너뛰기, 도착지점은 겹치기 가능
		if (map[nextPos].mal && nextPos != goalIdx)
			continue;

		//말 이동, 다음 턴으로 진행
		map[currentPos].mal = false;
		map[nextPos].mal = true;
		malPos[i] = nextPos;
		dfs(diceIdx + 1, sum + map[nextPos].value);

		//백트랙킹
		map[currentPos].mal = true;
		map[nextPos].mal = false;
		malPos[i] = currentPos;
	}	
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	for (int i = 0; i < 10; i++) {
		cin >> dice[i];
	}

	dfs(0, 0);
	cout << result;
	return 0;
}