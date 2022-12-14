#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

short N, M;//N은 행 M은 열
short _array[10][10];//3~8의 인덱스 사용한다. 인덱스9의 경우는 그냥 비어놓기 위함
short dx[4] = { 0,0,-1,1 };
short dy[4] = { -1,1,0,0 };
short high_score;
vector<pair<short, short>> v;


void spread_virus(short __array[][10], short x, short y) {
	short newx, newy;
	for (short k = 0; k < 4; k++) {
		newx = x + dx[k];
		newy = y + dy[k];
		if (newx<1 || newy<1 || newx>N || newy>M)
			continue;
		if (__array[newx][newy] == 0) {
			__array[newx][newy] = 2;
			spread_virus(__array, newx, newy);
		}
	}
}

void count_space(short __array[][10]) {
	short score = 0;
	for (short i = 1; i <= N; i++) {
		for (short j = 1; j <= M; j++) {
			if (__array[i][j] == 0)
				score++;
		}
	}
	high_score = max(high_score, score);
}

void spread_and_count() {			//바이러스 퍼뜨리고 score카운트
	short __array[10][10];
	for (short i = 1; i <= N; i++) {
		for (short j = 1; j <= M; j++) {	//0은 빈칸, 1은 벽, 2는 바이러스
			__array[i][j] = _array[i][j];
		}
	}

	for (unsigned short j = 0; j < v.size(); j++) {
		spread_virus(__array, v[j].first, v[j].second);
	}
	count_space(__array);
}

void dfs(short count) {		//구현1 벽 3개 설치
	if (count >= 3) {
		spread_and_count();
		return;
	}

	for (short i = 1; i <= N; i++) {
		for (short j = 1; j <= M; j++) {
			if (_array[i][j] == 0) {
				_array[i][j] = 1;
				dfs(count + 1);

				_array[i][j] = 0;
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;

	short a;
	for (short i = 1; i <= N; i++) {
		for (short j = 1; j <= M; j++) {	//0은 빈칸, 1은 벽, 2는 바이러스
			cin >> a;
			_array[i][j] = a;
			if (a == 2)
				v.push_back(make_pair(i, j));
		}
	}

	int x[3] = { 0 };
	int y[3] = { 0 };
	dfs(0);

	cout << high_score;
}