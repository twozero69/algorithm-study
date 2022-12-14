#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

vector<pair<int, short>> node_array[1001];
int shortrecord[1001];
bool visited[1001];


short current, here;
int start_to_current, start_to_here;

void dijkstra(int start) {
	priority_queue<pair<int, short>> pq;
	pq.push(make_pair(0, start));
	shortrecord[start] = 0;

	while (!pq.empty()) {
		current = pq.top().second;
		start_to_current = -pq.top().first;
		pq.pop();

		if (visited[current] == true)		//방문체크까지 하면 훨씬 빠름
			continue;

		visited[current] = true;

		for (unsigned int i = 0; i < node_array[current].size(); i++) {
			here = node_array[current][i].second;
			start_to_here = node_array[current][i].first + start_to_current;

			if (start_to_here < shortrecord[here]) {
				shortrecord[here] = start_to_here;
				pq.push(make_pair(-shortrecord[here], here));
			}
		}
	}
}

int main() {
	short N;
	int M;
	int u, v, c;
	int starting, end;
	cin >> N >> M;
	for (int j = 1; j <= N; j++)
		shortrecord[j] = INT_MAX;

	for (int i = 0; i <M; i++) {
		cin >> u >> v >> c;
		node_array[u].push_back(make_pair(c, v));
	}
	cin >> starting >> end;
	dijkstra(starting);
	cout << shortrecord[end];
}