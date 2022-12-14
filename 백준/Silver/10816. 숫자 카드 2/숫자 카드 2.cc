#include <iostream>
using namespace std;

int N;
int count_[20000001] ;
int M;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	int tmp;
	for (int i = 0; i < N; i++) {
		cin >> tmp;
		tmp += 10000000;
		count_[tmp]++;
	}

	cin >> M;
	for (int i = 0; i < M; i++) {
		cin >> tmp;
		tmp += 10000000;
		cout << count_[tmp] << ' ';
	}

	return 0;
}