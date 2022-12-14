#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

bool visited_DFS[1001];
bool visited_BFS[1001];

vector<int> array_node[1001];

int node_number;
int line_number;
int starting_node;

void node_info_push(int a, int b) {
	array_node[a].push_back(b);
	array_node[b].push_back(a);
}

void dfs(int x) {		//재귀함수로 할거임
	if (visited_DFS[x])
		return;

	visited_DFS[x] = true;
	printf("%d ", x);

	for (unsigned int i = 0; i < array_node[x].size(); i++) {
		dfs(array_node[x][i]);
	}
}

void bfs(int start) {
	queue<int> q;
	q.push(start);
	visited_BFS[start] = true;
	
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		printf("%d ", x);
		for (unsigned int i = 0; i < array_node[x].size(); i++) {
			int y = array_node[x][i];
			if (!visited_BFS[y]) {
				q.push(y);
				visited_BFS[y] = true;
			}
		}
	}
}

int main() {
	scanf("%d %d %d", &node_number, &line_number, &starting_node);
	int a, b;

	for (int i = 0; i < line_number; i++) {
		scanf("%d %d", &a, &b);
		node_info_push(a, b);
	}

	for (int j = 1; j <= node_number; j++) {
		sort(array_node[j].begin(), array_node[j].end());
	}

	dfs(starting_node);
	printf("\n");
	bfs(starting_node);
}