#include <stdio.h>
using namespace std;

int N;
int dp[31];

void init()
{
	scanf("%d", &N);
	
	dp[0] = 1;
	dp[2] = 3;
}

void solve()
{
	for (int i = 3; i <= N; i++)
	{
		//홀수인 경우
		if (i % 2 == 1)
			continue;

		//짝수인 경우
		dp[i] = dp[i - 2] * 3;
		for (int j = i - 4; j >= 0; j -= 2)
			dp[i] += dp[j] * 2;
	}
}

int main()
{
	init();
	solve();
	printf("%d", dp[N]);

	return 0;
}