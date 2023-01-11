/*
-문제 정리
	N개의 원소를 가지는 배열을 M개의 구간으로 나눠 구간에 속하는 수의 합이 최대값이 되게 하는 프로그램.
	구간과 구간 사이는 1개 이상 떨어져 있음.
	구간을 나누는 방법을 잘 생각해 볼 것.

	N = 1 ~ 100
	M = 1 ~ N / 2
	원소는 -32768 ~ 32767의 값을 가짐.

-풀이
	1. 완전탐색
		단순히 구간에 속하나 안속하나의 2택으로 생각하면 2^M보다 크고 2^N보단 작음.
		N이 100, M이 10까지가 최대이므로 2^10 ~ 2^100 => 너무 느림.

	2. dp
		현재 상태와 다음 상태를 나누는 요소의 후보는 아래와 같음.
			(1)배열에서 몇 번째 수까지 취급
			(2)현재까지 분리된 구간의 수

		2차원 배열을 dp[idx][sector]의 형태로 만들고 idx번째 수까지 취급하고 sector개의 구간으로 나눌 때의 최대값을 저장함.
		idx번째 수에 대해서 (1)구간에 포함하는 경우 (2)구간에 포함하지 않는 경우의 두가지로 생각함.
			(1)구간에 포함하는 경우 (dp[k][sector - 1] | arr[k+1]은 구간 x | arr[k] ~ arr[idx]을 sector번쨰 구간)
				dp[idx][sector] = max(dp[k][sector - 1] + arr[k + 2] + arr[k + 3] + ... + arr[idx]) //k = sector * 2 ~ idx - 2
			(2)구간에 포함하지 않는 경우
				dp[idx][sector] = dp[idx - 1][sector]

-주의사항
	1.
	배열에 음수도 포함되기 때문에 dp배열의 초기값을 신경써주어야함.
	전역변수로 dp배열을 선언하여 모든 값들이 0으로 초기화되어 음수와의 비교에서 문제가 발생함.
	
	2.
	sector = 0일 때는 다음의 점화식을 따름.
		(1)구간에 포함하는 경우
			dp[idx][0] = sum(arr[0] ~ arr[idx]), sum(arr[1] ~ arr[idx]), ... , arr[idx] 중에서 가장 큰 값을 선택
		(2)구간에 포함하지 않는 경우
			dp[idx][0] = dp[idx - 1][0]

-잡담
	dp배열을 작성하기 위한 2중 for문을 작성할 때
	sector, idx 순으로 순환할지 idx, sector 순서로 순환할지 결정하는 것이 어려웠음.
	어떤 순서로 해도 상관없는 경우도 있고 정해진 순서가 있는 경우도 있음.

	다만 순환순서에 따라 구현이 복잡해지거나 쉬워지므로 어느 쪽이 더 간편할지 고려해야함.

	애매할 때는 체크배열과 재귀호출로 top-down 형태로 구현하면 간단하게 구현할 수 있음.
*/

#include <stdio.h>

int N, M;
int arr[100];
int dp[100][50];
int sum[100][100];

void init()
{
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
		scanf("%d", &arr[i]);

	//sum배열 작성
	for (int start = 0; start < N; start++)
	{
		sum[start][start] = arr[start];
		for (int end = start + 1; end < N; end++)
			sum[start][end] = sum[start][end - 1] + arr[end];
	}

	//dp배열 초기화
	for (int idx = 0; idx < N; idx++)
	{
		for (int sector = 0; sector < M; sector++)
		{
			dp[idx][sector] = -3276800;
		}
	}

	//idx = 0
	dp[0][0] = arr[0];
	if (N == 1)
		return;

	//idx = 1
	dp[1][0] = sum[0][1];
	if (dp[1][0] < arr[0])
		dp[1][0] = arr[0];
	if (dp[1][0] < arr[1])
		dp[1][0] = arr[1];
}

void solve()
{
	//idx = 2 ~ N - 1
	for (int idx = 2; idx < N; idx++)
	{
		//sector = 0
		{
			//arr[idx]를 포함하지 않는 경우
			dp[idx][0] = dp[idx - 1][0];

			//arr[idx]를 포함하는 경우
			for (int k = 0; k <= idx; k++)
			{
				if (dp[idx][0] < sum[k][idx])
					dp[idx][0] = sum[k][idx];
			}
		}

		//sector = 1 ~ M - 1
		int end_sector = idx / 2;
		if (end_sector >= M)
			end_sector = M - 1;

		for (int sector = 1; sector <= end_sector; sector++)
		{
			//arr[idx]를 포함하지 않는 경우
			dp[idx][sector] = dp[idx - 1][sector];

			//arr[idx]를 포함하는 경우
			int end_k = idx - 2;
			for (int k = (sector - 1) * 2; k <= end_k; k++) //idx = sector * 2 부터 dp배열에 의미 있는 값이 들어있음
			{
				int term = dp[k][sector - 1] + sum[k + 2][idx];
				if (term > dp[idx][sector])
					dp[idx][sector] = term;
			}
		}
	}
}

int main()
{
	init();
	solve();
	printf("%d", dp[N - 1][M - 1]);

	return 0;
}