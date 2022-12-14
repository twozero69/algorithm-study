#include <iostream>
#include <vector>
using namespace std;

bool shortcut_A[20001];
bool shortcut_B[20001];
vector<int> node_array[20001];
bool detect[6];

void dfs_A(int x, int y);
void dfs_B(int x, int y);

void dfs_A(int x, int y) {				//이분그래프의 A측에대한 처리. 방문한 노드 x가 A측임
	if (shortcut_B[x]) {
		detect[y] = false;
		return;
	}
	else if (shortcut_A[x])
		return;

	shortcut_A[x] = true;

	for (int i = 0; i < node_array[x].size(); i++) {
		dfs_B(node_array[x][i], y);
	}
}

void dfs_B(int x, int y) {				//이분그래프의 B측에대한 처리. 방문한 노드 x가 B측임
	if (shortcut_A[x]) {
		detect[y] = false;
		return;
	}
	else if (shortcut_B[x])
		return;

	shortcut_B[x] = true;

	for (int i = 0; i < node_array[x].size(); i++) {
		dfs_A(node_array[x][i], y);
	}
}

void push_array(int a, int b) {
	node_array[a].push_back(b);
	node_array[b].push_back(a);
}

int main() {
	int K;					//케이스의 개수
	scanf("%d", &K);

	for (int i = 1; i <= K; i++) {
		int V, E;			//노드수, 간선수
		scanf("%d %d", &V, &E);

		detect[i] = true;

		for (int j = 1; j <= V; j++) {
			shortcut_A[j] = false;
			shortcut_B[j] = false;
			node_array[j].clear();
		}

		int a, b;

		for (int k = 0; k < E; k++) {
			scanf("%d %d", &a, &b);
			push_array(a, b);
		}

		for (int n = 1; n <= V; n++) {			//dfs실행파트
			if (shortcut_A[n])
				continue;
			else if (shortcut_B[n])
				continue;
			dfs_A(n,i);
		}
	}

	for (int m = 1; m <= K; m++) {
		if (detect[m])
			printf("YES");
		else
			printf("NO");
		printf("\n");
	}
}