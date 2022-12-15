#include <stdio.h>

int N;
int num[1000];
int dp[1000];
int result;

void init()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &num[i]);

	dp[0] = num[0];
	result = 1;
}

void solve()
{
	for (int i = 1; i < N; i++)
	{
		//dp[0]
		if (dp[0] > num[i])
			dp[0] = num[i];

		//dp[1] ~ dp[result - 1]
		for (int j = 0; j < result - 1; j++)
		{
			if (dp[j] < num[i] && num[i] < dp[j + 1])
				dp[j + 1] = num[i];
		}

		//dp[result]
		if (dp[result - 1] < num[i])
			dp[result++] = num[i];
	}
}

int main()
{
	init();
	solve();
	printf("%d", result);

	return 0;
}