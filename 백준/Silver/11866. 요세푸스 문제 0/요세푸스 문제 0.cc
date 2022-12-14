#include <iostream>
#include <vector>
using namespace std;

int N, K;
vector<int> v;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> K;
	for (int i = 1; i <= N; i++)
		v.push_back(i);

	cout<<'<';
	int idx = K - 1;
	while (v.size()!=1) {
		cout << v[idx] << ", ";
		v.erase(v.begin() + (idx));
		idx = (idx + K - 1) % v.size();
	}
	cout << v[0] << '>';
	return 0;
}