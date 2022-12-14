#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <memory.h>
#define INT_MAX 2147483647
using namespace std;

int N;
int arr[20][20];
int dy[4] = { 0, 0, -1, 1 };
int dx[4] = { -1, 1, 0, 0 };

bool compare(pair<int, int> a, pair<int, int> b) {
	if (a.first == b.first)
		return a.second < b.second;

	return a.first < b.first;
}

bool bfs(int& row, int& col, int& size, int& result) {
	queue<pair<pair<int, int>, int>> q;	//first:pair<int, int> sharq position, second: move num
	q.push(make_pair(make_pair(row, col), 0));
	vector<pair<int, int>> v;
	int moveLimit = INT_MAX;
	bool check[20][20];
	memset(check, false, sizeof(check));
	while (!q.empty()) {
		pair<pair<int, int>, int> sharq = q.front();
		q.pop();

		if (sharq.first.first < 0 || sharq.first.first >= N || sharq.first.second < 0 || sharq.first.second >= N)
			continue;

		if (size < arr[sharq.first.first][sharq.first.second] || check[sharq.first.first][sharq.first.second] || sharq.second > moveLimit)
			continue;

		check[sharq.first.first][sharq.first.second] = true;

		if (1 <= arr[sharq.first.first][sharq.first.second] && arr[sharq.first.first][sharq.first.second] < size) {
			v.push_back(sharq.first);
			moveLimit = sharq.second;
			continue;
		}

		for (int i = 0; i < 4; i++) {
			q.push(make_pair(make_pair(sharq.first.first + dy[i], sharq.first.second + dx[i]), sharq.second + 1));
		}
	}

	if (v.empty())
		return false;
	sort(v.begin(), v.end(), compare);
	row = v[0].first;
	col = v[0].second;
	arr[row][col] = 0;
	result += moveLimit;
	return true;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	pair<int, int> sharq;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 9) {
				sharq.first = i;
				sharq.second = j;
				arr[i][j] = 0;
			}
		}
	}

	int sharqSize = 2;
	int sharqEat = 0;
	int result = 0;
	while (bfs(sharq.first, sharq.second, sharqSize, result)) {
		sharqEat++;
		if (sharqEat == sharqSize) {
			sharqEat = 0;
			sharqSize++;
		}
	}
	
	cout << result;
	return 0;
}