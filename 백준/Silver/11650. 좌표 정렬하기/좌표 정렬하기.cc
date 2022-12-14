#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N;
vector<pair<int, int>> v;

bool compare(pair<int, int> a, pair<int, int> b) {
	if (a.first != b.first)
		return a.first < b.first;
	return a.second < b.second;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	int x, y;
	for (int i = 0; i < N; i++) {
		cin >> x >> y;
		v.push_back(make_pair(x, y));
	}

	sort(v.begin(), v.end());
	for (int i = 0; i < v.size(); i++)
		cout << v[i].first << ' ' << v[i].second << '\n';
	
	return 0;
}