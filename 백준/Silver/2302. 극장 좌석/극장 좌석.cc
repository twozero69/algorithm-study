/*
-문제 정리

	극장의 좌석에 사람들이 앉는 경우의 수 구하기.

	좌석은 한 줄로 1 ~ N의 번호가 매겨짐.
	회원의 티켓에는 좌석의 번호가 적혀 있음.
	ㄴ일반회원은 번호 - 1, 번호, 번호 + 1 중 하나에 앉을 수 있음.
	ㄴVIP회원은 지정 번호에만 앉을 수 있음.
	ㄴVIP회원의 좌석번호는 입력으로 주어짐.


-풀이
	
	1. 완전탐색
		번호 - 1, 번호, 번호 + 1의 3개의 자리에 n명의 관객을 배치하고 각 케이스마다 모든 좌석이 찼는지 체크.
		관객배치 = O(3^N), 좌석체크 = O(N)이므로 너무 느림.

	2. dp
		dp배열에 k번까지의 좌석배치 경우의 수를 저장.
		O(N)으로 처리.

		vip를 고려하지 않는다면 들어갈 좌석은 k, k - 1 이므로 다음의 점화식으로 표현 가능.
		dp[k] = dp[k - 1] + dp[k - 2]

		만약 k가 vip라면 들어갈 좌석은 k뿐이므로 다음의 점화식으로 표현 가능.
		dp[k] = dp[k - 1]

		만약 k - 1이 vip라면 들어갈 좌석은 k뿐이므로 다음의 점화식으로 표현 가능.
		dp[k] = dp[k - 1]

		점화식 =>	if (k가 vip, k - 1이 vip)
						dp[k] = dp[k - 1]
					else
						dp[k] = dp[k - 1] + dp[k - 2]
*/

#include <stdio.h>

int N, M;	//N = 1 ~ 40, M = 0 ~ N
bool vip[41];
unsigned int dp[41];

void init()
{
	scanf("%d %d", &N, &M);

	int term;
	for (int i = 0; i < M; i++)
	{
		scanf("%d", &term);
		vip[term] = true;
	}

	dp[1] = 1;
	if (vip[1] || vip[2])
		dp[2] = 1;
	else
		dp[2] = 2;
}

void solve()
{
	for (int k = 3; k <= N; k++)
	{
		if (vip[k] || vip[k - 1])
			dp[k] = dp[k - 1];
		else
			dp[k] = dp[k - 1] + dp[k - 2];
	}
}

int main()
{
	init();
	solve();
	printf("%u", dp[N]);

	return 0;
}