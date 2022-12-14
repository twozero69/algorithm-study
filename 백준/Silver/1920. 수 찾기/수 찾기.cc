#include <iostream>
#include <algorithm>
using namespace std;

int N;
int arrN[100000];
int M;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arrN[i];
	}

	sort(arrN, arrN + N);

	cin >> M;
	int term;
	for (int i = 0; i < M; i++) {
		cin >> term;
		if (binary_search(arrN, arrN + N, term))
			cout << '1' << '\n';
		else
			cout << '0' << '\n';
	}

	return 0;
}