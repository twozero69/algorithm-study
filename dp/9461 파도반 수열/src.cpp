#include <iostream>
using namespace std;

int T, N;
unsigned long long dp[101] = { 0, 1, 1, 1, 2, 2, 3, 4, 5, 7, 9, };

void getDp()
{
	if (N < 11)
		return;

	for (int i = 11; i <= N; i++)
		dp[i] = dp[i - 1] + dp[i - 5];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> T;
	for (int i = 0; i < T; i++)
	{
		cin >> N;
		getDp();
		cout << dp[N] << '\n';
	}

	return 0;
}