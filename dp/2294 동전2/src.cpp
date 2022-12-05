#include <iostream>
#include <algorithm>
using namespace std;

int N, K;
int coin[100];
int dp[10001];

bool compare(int& a, int& b)
{
	return a > b;
}

void init()
{
	cin >> N >> K;
	for (int i = 0; i < N; i++)
		cin >> coin[i];

	dp[0] = 0;
	for (int i = 1; i <= K; i++)
		dp[i] = -1;

	sort(coin, coin + N, compare);
}

void getDp()
{
	for (int r = 0; r < N; r++)
	{
		int current_coin = coin[r];

		for (int c = current_coin; c <= K; c++)
		{
			int term = c - current_coin;
			if (term < 0 || dp[term] == -1)
				continue;

			int term2 = dp[term] + 1;
			if (dp[c] == -1 || dp[c] > term2)
				dp[c] = term2;
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	getDp();
	cout << dp[K];

	return 0;
}