#include <iostream>
#include <vector>
using namespace std;

int N, M;
int water[50][50];
int dy[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };
int dx[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dy2[4] = { 1, 1, -1, -1 };
int dx2[4] = { 1, -1, 1, -1 };
vector<pair<int, int>> cloud;

void rain(int dist, int speed) {
	bool check[50][50];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			check[i][j] = false;
		}
	}

	//구름 이동하고 물증가
	int step = speed % N;
	for (int i = 0; i < cloud.size(); i++) {
		cloud[i].first = (cloud[i].first + dy[dist] * step + N) % N;
		cloud[i].second = (cloud[i].second + dx[dist] * step + N) % N;
		water[cloud[i].first][cloud[i].second]++;
		check[cloud[i].first][cloud[i].second] = true;
	}

	//물복사버그
	for (int i = 0; i < cloud.size(); i++) {
		for (int j = 0; j < 4; j++) {
			int nearY = cloud[i].first + dy2[j];
			int nearX = cloud[i].second + dx2[j];

			if (nearY < 0 || nearY >= N || nearX < 0 || nearX >= N)
				continue;

			if (water[nearY][nearX] == 0)
				continue;

			water[cloud[i].first][cloud[i].second]++;
		}
	}

	cloud.clear();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (check[i][j] || water[i][j] < 2)
				continue;

			water[i][j] -= 2;
			cloud.push_back(make_pair(i, j));
		}
	}
}

int getResult() {
	int sum = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			sum += water[i][j];
		}
	}

	return sum;
}

int main() {
	ios::sync_with_stdio(false);
	cout.tie(NULL);
	cin.tie(NULL);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> water[i][j];
		}
	}

	cloud.push_back(make_pair(N - 1, 0));
	cloud.push_back(make_pair(N - 1, 1));
	cloud.push_back(make_pair(N - 2, 0));
	cloud.push_back(make_pair(N - 2, 1));
	for (int i = 0; i < M; i++) {
		int dist, step;
		cin >> dist >> step;
		rain(dist - 1, step);
	}

	cout << getResult();
	return 0;
}