#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#define INT_MAX 2147483647
using namespace std;

int N, E;
vector<pair<int, int>> edge[801];	//[]는 노드1, first는 node2, second는 edge의 cost
int v1, v2;
int result1[801];
int resultv1[801];
int resultv2[801];

void dijkstra(int start, int* arr) {
	//stl 우선순위 큐에서 pair사용시 second를 기준으로 정렬
	priority_queue<pair<int, int>> Q;	//first는 노드번호, second는 거리정보
	fill_n(arr, N + 1, INT_MAX);

	arr[start] = 0;
	Q.push(make_pair(start, arr[start]));
	while (!Q.empty()) {
		//큐에서 1개 뽑아옴
		int currentNode = Q.top().first;	//현재 노드의 번호
		int currentCost = -Q.top().second;	//이것은 arr[currentNode]와 일치하는 값임
		Q.pop();

		//약간의 최적화
		if (currentCost > arr[currentNode])
			continue;

		for (int i = 0; i < edge[currentNode].size(); i++) {
			int nextNode = edge[currentNode][i].first;
			int nextCost = currentCost + edge[currentNode][i].second;

			//비용 업데이트
			if (nextCost < arr[nextNode]) {
				arr[nextNode] = nextCost;
				Q.push(make_pair(nextNode, -nextCost));	
			}
		}
	}
}

int detect() {
	//최단경로 탐색
	dijkstra(1, result1);
	dijkstra(v1, resultv1);
	dijkstra(v2, resultv2);
	
	//1. 1->v1->v2->N
	int tmp1 = INT_MAX;
	if (result1[v1] != INT_MAX && resultv1[v2] != INT_MAX && resultv2[N] != INT_MAX)
		tmp1 = result1[v1] + resultv1[v2] + resultv2[N];

	//2. 1->v2->v1->N
	int tmp2 = INT_MAX;
	if (result1[v2] != INT_MAX && resultv2[v1] != INT_MAX && resultv1[N] != INT_MAX)
		tmp2 = result1[v2] + resultv2[v1] + resultv1[N];

	//경로가 없는지 확인
	if (tmp1 == INT_MAX && tmp2 == INT_MAX)
		return -1;
	else
		return tmp1 < tmp2 ? tmp1 : tmp2;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> E;
	int node1, node2, cost;
	for (int i = 0; i < E; i++) {
		cin >> node1 >> node2 >> cost;
		edge[node1].push_back(make_pair(node2, cost));
		edge[node2].push_back(make_pair(node1, cost));
	}
	cin >> v1 >> v2;

	cout << detect();
	return 0;
}