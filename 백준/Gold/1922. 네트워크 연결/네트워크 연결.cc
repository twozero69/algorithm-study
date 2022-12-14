#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct edge {
	int node1;
	int node2;
	int cost;
};

bool compare(edge a, edge b) {
	return a.cost < b.cost;
}

int V, E;
vector<edge> edges;
int parent[1001];

int getParent(int num) {
	if (parent[num] == num)
		return num;

	return parent[num] = getParent(parent[num]);
}

void unionParent(int a, int b) {
	parent[getParent(a)] = getParent(b);
}

bool checkUnion(int a, int b) {
	if (getParent(a) == getParent(b))
		return true;
	else
		return false;
}

int kruskal() {
	int result = 0;
	int count_ = 0;
	for (int i = 0; i < edges.size(); i++) {
		if (count_ == V - 1)
			break;

		if (checkUnion(edges[i].node1, edges[i].node2))
			continue;

		result += edges[i].cost;
		unionParent(edges[i].node1, edges[i].node2);
		count_++;
	}

	return result;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> V >> E;
	int node1, node2, cost;
	for (int i = 0; i < E; i++) {
		cin >> node1 >> node2 >> cost;
		edge term;
		term.node1 = node1;
		term.node2 = node2;
		term.cost = cost;
		edges.push_back(term);
	}

	sort(edges.begin(), edges.end(), compare);

	for (int i = 1; i <= V; i++) {
		parent[i] = i;
	}

	cout << kruskal();
	return 0;
}