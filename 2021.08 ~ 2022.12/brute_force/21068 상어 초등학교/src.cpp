#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;

int N; // 3 ~ 20
int classRoom[21][21] = { {0, }, }; // 1 ~ 20�� �ε����� ���.
int dx[4] = { 0, 0, 1, -1 };
int dy[4] = { 1, -1, 0, 0 };

typedef struct position {
	int row = 0;
	int col = 0;
}POSITION;

POSITION studentPosition[401];

typedef struct info {
	int row = 0;
	int col = 0;
	int likeCnt = 0;
	int emptyCnt = 0;
}INFO;

/*
	1 ~ 400 / 0 ~ 4�� �ε����� ���.

	0 : �л���ȣ
	1 ~ 4 : �����ϴ� �л�
*/
int like[401][5];




//std::sort()�� true�� ����ΰ� false�� �ڸ���ȯ
bool compare(INFO A, INFO B) {
	//1. ���� �����ϴ� �л� ���� ��
	if (A.likeCnt != B.likeCnt)
		return A.likeCnt > B.likeCnt;

	//2. ���� ���ڸ� ���� ��
	if (A.emptyCnt != B.emptyCnt)
		return A.emptyCnt > B.emptyCnt;

	//3. ���� ��ȣ ���� ��
	if (A.row != B.row)
		return A.row < B.row;

	//4. ���� ��ȣ ���� ��
	return A.col < B.col;
};

void placeStudent(int idx) {
	vector<INFO> container;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			//��ĭ�� �ƴ϶�� �н�
			if (classRoom[i][j] != 0)
				continue;

			//���ο� �ڸ��ĺ� �߰�
			INFO term;
			term.row = i;
			term.col = j;

			//1. �����ϴ� �л��� �����ϴ��� üũ
			for (int k = 1; k <= 4; k++) {
				int likeNum = like[idx][k];
				POSITION likePosition = studentPosition[likeNum];

				if (likePosition.col == 0 || likePosition.row == 0)
					continue;

				int dist = abs(i - likePosition.row) + abs(j - likePosition.col);
				if (dist > 1)
					continue;

				term.likeCnt++;
			}

			//2. ������ ĭ �� ����ִ� ĭ üũ
			for (int k = 0; k < 4; k++) {
				int nearRow = i + dy[k];
				int nearCol = j + dx[k];
				if (nearRow < 1 || nearRow > N || nearCol < 1 || nearCol > N)
					continue;

				if (classRoom[nearRow][nearCol] != 0)
					continue;

				term.emptyCnt++;
			}

			container.push_back(term);
		}
	}
	
	//��ġ�� �ڸ��� ����
	sort(container.begin(), container.end(), compare);
	INFO newStudent = container[0];

	//��ó��
	int studentNum = like[idx][0];
	studentPosition[studentNum].row = newStudent.row;
	studentPosition[studentNum].col = newStudent.col;
	classRoom[newStudent.row][newStudent.col] = studentNum;
};

int calcResult() {
	int result = 0;

	for (int i = 1; i <= N*N; i++){
		int likeCnt = 0;
		int myNum = like[i][0];
		POSITION myPosition = studentPosition[myNum];
		for (int j = 1; j <= 4; j++) {
			int likeNum = like[i][j];
			POSITION likePosition = studentPosition[likeNum];

			int dist = abs(myPosition.row - likePosition.row) + abs(myPosition.col - likePosition.col);
			if (dist > 1)
				continue;

			likeCnt++;
		}

		switch (likeCnt) {
		case 0:
			break;
		case 1:
			result += 1;
			break;
		case 2:
			result += 10;
			break;
		case 3:
			result += 100;
			break;
		case 4:
			result += 1000;
			break;
		}
	}

	return result;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 1; i <= N*N; i++) {
		for (int j = 0; j < 5; j++) {
			cin >> like[i][j];
		}
	}
	
	for (int i = 1; i <= N*N; i++) {
		placeStudent(i);
	}

	cout << calcResult();
	return 0;
};