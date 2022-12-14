#include <iostream>
#define INT_MAX 100000000
using namespace std;

int n;	//도시의 개수
int m;	//버스의 개수
int table[101][101];	//i->j로 가는 최소비용을 저장

void floid() {
	/*
	플로이드 와샬 알고리즘
	start->end와 start->relay->end를 비교하여 테이블을 업데이트
	3개의 for문 사용.
	첫번째는 relay
	두번째와 세번째는 start와 end
	*/

	for (int relay = 1; relay <= n; relay++) {
		for (int start = 1; start <= n; start++) {
			for (int end = 1; end <= n; end++) {
				int term = table[start][relay] + table[relay][end];
				table[start][end] = table[start][end] < term ? table[start][end] : term;
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == j) {
				table[i][j] = 0;
				continue;
			}
			table[i][j] = INT_MAX;
		}
	}

	int start, end, cost;
	for (int i = 0; i < m; i++) {
		cin >> start >> end >> cost;
		table[start][end] = table[start][end] < cost ? table[start][end] : cost;
	}

	floid();
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (table[i][j] == 100000000)
				table[i][j] = 0;

			cout << table[i][j] << ' ';
		}
		cout << '\n';
	}

	return 0;
}