#include <iostream>
using namespace std;

int N;
unsigned long dp[91];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N;
	
	dp[0] = 0;
	dp[1] = 1;
	for (int i = 2; i <= N; i++) {
		dp[i] = dp[i - 1] + dp[i - 2];
	}

	cout << dp[N];
	return 0;
}