#include <iostream>
using namespace std;

/*
-생각난 방법
1. dp
	'K개의 수로 N을 만드는 경우의 수' = 'K-1개의 수로 0, 1, 2 ... N을 만드는 경우의 수의 총합'
	'K개의 수로 N-1을 만드는 경우의 수' = 'K-1개의 수로 0, 1, 2 ... N-1을 만드는 경우의 수의 총합'
	=> 점화식 dp[k][n] = dp[k][n - 1] + dp[k - 1][n];
	O(N x K)

2. 완전탐색
	0 ~ N까지 순환하는 for문을 K개 중첩하여 구현가능.
	O(N^K) -> 너무느림.

-메모리 최적화
	2차원 배열을 사용하지 않고 col만 고려한 1차원 배열을 재탕해서 사용.
*/

int N, K;
int dp[201];

void init()
{
	cin >> N >> K;

	for (int n = 0; n <= N; n++)
		dp[n] = 1;
}

void solve()
{
	for (int k = 2; k <= K; k++)
	{
		for (int n = 1; n <= N; n++)
		{
			dp[n] = (dp[n] + dp[n - 1]) % 1000000000;
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	solve();
	cout << dp[N];

	return 0;
}