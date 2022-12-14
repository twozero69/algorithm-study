#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;

int N, M, D;	//N행의수 M열의수 D 공격거리
int __array[16][16];
int termarray[16][16];
int highscore;

bool comp(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b) {
	if (a.first == b.first)
		return a.second.second < b.second.second;
	return a.first < b.first;
}

int playgame(int* arr) {
	int _score = 0;
	for (int i = 0; i < N; i++) {
		vector<pair<int, pair<int, int>>> v[3];
		for (int m = 0; m < 3; m++) {
			for (int a = N - i; a >= 1; a--) {
				for (int k = 1; k <= M; k++) {
					int dist = abs(k - arr[m]) + N - i - a + 1;
					if (dist <= D && termarray[a][k] == 1)
						v[m].push_back(make_pair(dist, make_pair(a, k)));
				}
			}
			sort(v[m].begin(), v[m].end(), comp);
		}
		for (int n = 0; n < 3; n++) {
			if (!v[n].empty() && termarray[v[n][0].second.first][v[n][0].second.second] == 1) {
				_score++;
				termarray[v[n][0].second.first][v[n][0].second.second] = 0;
			}
		}
	}
	return _score;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M >> D;

	int term;
	for (int i = 1; i <= N; i++) {		//0은 빈칸 1은 적이 있는 칸
		for (int j = 1; j <= M; j++) {
			cin >> term;
			__array[i][j] = term;
		}
	}


	for (int A = 1; A <= M - 2; A++) {
		for (int B = A + 1; B <= M - 1; B++) {
			for (int C = B + 1; C <= M; C++) {

				for (int i = 1; i <= N; i++) {		//0은 빈칸 1은 적이 있는 칸
					for (int j = 1; j <= M; j++) {
						termarray[i][j] = __array[i][j];
					}
				}
				int arr[3] = { A, B, C };
				int __score = playgame(arr);
				if (highscore < __score)
					highscore = __score;
			}
		}
	}

	cout << highscore;
}