#include <iostream>
#include <vector>
#include <string.h>
#include <math.h>
#include <limits.h>
using namespace std;

int N;
int ingu[11];
int _size[11];
vector<int> graph[11];
int result = INT_MAX;
int checknum;
bool check[11];
bool check1[11], check2[11];
int visit;

void dfs1(int count) {
	if (check1[count])
		return;

	check1[count] = true;
	visit++;

	int next;
	for (int i = 0; i < _size[count]; i++) {
		next = graph[count][i];
		if (check[next]) {
			dfs1(next);
		}
	}
}

bool checking1() {
	bool flag = true;
	for (int i = 1; i <= N; i++) {
		if (check[i])
			if (!check1[i])
				flag = false;
	}
	return flag;
}

void dfs2(int count) {
	if (check2[count])
		return;
	
	check2[count] = true;
	visit++;

	int next;
	for (int i = 0; i < _size[count]; i++) {
		next = graph[count][i];
		if (!check[next]) {
			dfs2(next);
		}
	}
}

void calculate() {
	int term = 0;
	for (int i = 1; i <= N; i++) {
		if (check[i])
			term += ingu[i];
		else
			term -= ingu[i];
	}
	int term2 = abs(term);

	result = result > term2 ? term2 : result;
}

void bruteforce(int count) {		//그룹1은 true 그룹2는 false
	for (int i = count; i <= N; i++) {
		if (!check[i]) {
			check[i] = true;

			memset(check1, false, sizeof(bool) * 11);
			visit = 0;
			dfs1(i);
			if (checking1()) {
				for (int j = 1; j <= N; j++) {
					if (!check[j]) {
						memset(check2, false, sizeof(bool) * 11);
						dfs2(j);

						if (visit == N) {
							calculate();
						}

						break;
					}
				}
			}

			bruteforce(i+1);

			check[i] = false;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> N;

	for (int i = 1; i <= N; i++) {
		cin >> ingu[i];
	}

	for (int j = 1; j <= N; j++) {
		cin >> _size[j];

		int connect;
		for (int k = 1; k <= _size[j]; k++) {
			cin >> connect;
			graph[j].push_back(connect);
		}
	}

	bruteforce(1);

	if (result == INT_MAX)
		cout << -1;
	else
		cout << result;
}