/*
-풀이
	점화식:	dp(n) = dp(n - 1) + dp(n - 2) * 2 + dp(n - 3) * 2 + ... + dp(0) * 2 + 2
			dp(n - 1) = dp(n - 2) + dp(n - 3) * 2 + ... + dp(0) * 2 + 2
			-> dp(n) = dp(n - 1) * 2 + dp(n - 2)

-배운점
	dp인 느낌이 들면 현재 단계에서 다음 단계로 넘어갈 때 어떻게 변화되는지 잘 고려해볼것.

-최적화
	점화식이 dp(n) = dp(n - 1) * 2 + dp(n - 2)이므로 100001사이즈의 배열을 쓸 것이 아니라 변수 3개면 됨.
*/

#include <stdio.h>

int N;
int dp_n, dp_n_1, dp_n_2;

void init()
{
	scanf("%d", &N);

	dp_n_1 = 1;
	dp_n = 3;
}

void solve()
{
	for (int i = 2; i <= N; i++)
	{
		dp_n_2 = dp_n_1;
		dp_n_1 = dp_n;
		dp_n = (dp_n_1 * 2 + dp_n_2) % 9901;
	}
}

int main()
{
	init();
	solve();
	printf("%d", dp_n);

	return 0;
}