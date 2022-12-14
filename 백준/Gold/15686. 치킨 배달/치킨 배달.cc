#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

int N = 0;
int M = 0;
vector<pair<int, int>> chicken;
vector<pair<int, int>> house;
int _select[13] = { 0, };	//선택된 치킨집번호들을 저장
int table[100][13] = { {0,}, };	//행부분이 집, 열부분이 치킨집.
int result = 2147483647;

void calcDist() {
	int term = 0;
	for (int i = 0; i < house.size(); i++) {
		int min = 2147483647;
		for (int j = 0; j < M; j++) {
			if (table[i][_select[j]] < min)
				min = table[i][_select[j]];
		}
		term += min;
	}

	result = result < term ? result : term;
}

void dfs(int count, int idx) {
	if (count == M) {
		calcDist();
		return;
	}

	int total = chicken.size() - M + count + 1;
	for (int i = idx; i < total; i++) {
		_select[count] = i;
		dfs(count + 1, i + 1);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	int term = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> term;
			switch (term) {
			case 1:
				house.push_back(make_pair(i, j));
				break;
			case 2:
				chicken.push_back(make_pair(i, j));
				break;
			}
		}
	}

	for (int i = 0; i < house.size(); i++) {
		for (int j = 0; j < chicken.size(); j++) {
			table[i][j] = abs(house[i].first - chicken[j].first) + abs(house[i].second - chicken[j].second);
		}
	}

	dfs(0, 0);
	cout << result;
	return 0;
}