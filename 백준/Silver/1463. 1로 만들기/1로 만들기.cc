#include <iostream>
using namespace std;

int N;
int DP[1000001];

int main() {
	cin >> N;
	DP[1] = 0;

	//bottom up
	for (int i = 2; i <= N; i++) {
		if (i % 6 == 0) {
			int div3 = DP[i / 3] + 1;
			int div2 = DP[i / 2] + 1;
			int sub = DP[i - 1] + 1;

			if (div3 > div2) {
				DP[i] = div2 < sub ? div2 : sub;
			}
			else {
				DP[i] = div3 < sub ? div3 : sub;
			}
		}
		else if (i % 3 == 0) {
			int div3 = DP[i / 3] + 1;
			int sub = DP[i - 1] + 1;
			DP[i] = div3 < sub ? div3 : sub;
		}
		else if (i % 2 == 0) {
			int div2 = DP[i / 2] + 1;
			int sub = DP[i - 1] + 1;
			DP[i] = div2 < sub ? div2 : sub;
		}
		else {
			DP[i] = DP[i - 1] + 1;
		}
	}

	cout << DP[N];
	return 0;
}