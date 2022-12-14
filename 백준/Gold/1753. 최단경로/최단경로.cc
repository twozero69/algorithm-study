#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

vector<pair<int, short>> node_array[20001];
int shortrecord[20001];
bool visited[20001];

short V, number;
int E;


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

		if (visited[current] == true)
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
	short u, v;
	int w;

	scanf("%hd %d", &V, &E);
	scanf("%hd", &number);

	for (int k = 1; k <= V; k++) {
		shortrecord[k] = INT_MAX;
	}

	for (int i = 0; i < E; i++) {
		scanf("%hd %hd %d", &u, &v, &w);
		node_array[u].push_back(make_pair(w, v));
	}

	dijkstra(number);

	for (int j = 1; j <= V; j++) {
		if (shortrecord[j] == INT_MAX) {
			printf("INF\n");
		}
		else {
			printf("%d\n", shortrecord[j]);
		}
	}
}