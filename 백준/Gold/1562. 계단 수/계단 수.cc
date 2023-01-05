/*
-문제 정리
	45656처럼 모든 자리의 수가 양 옆의 자리와 1만큼 차이가 나는 수를 '계단수'라고 한다.
	추가사항으로 0으로 시작하는 수는 계단수가 아님.
	숫자의 길이 N이 주어질 떄, 0 ~ 9가 모두 등장하는 계단수가 몇 개인지 출력하는 프로그램 작성.
	(N = 1 ~ 100)

-풀이
	1. 완전탐색
		O(10^N) => 너무 느림.

	2. dp
		뒷자리 숫자에 따라서 다음에 올 수 있는 수의 개수가 달라짐.
		0 -> 1
		2 ~ 8 -> -1 또는 +1
		9 -> 8

		이것을 응용하여 dp[n][back]의 형태의 배열을 사용하면 n개의 자리를 가지는 수에서 뒷자리가 back인 경우의 수를 저장가능함.
		다만 0 ~ 9의 숫자를 모두 가지고 있는지 체크하는 방법이 필요함.

		0 ~ 9를 비트마스킹을 통해 체크함.
		dp[n][back][check] 형태의 배열을 사용.

		O(N * 10 * 2^10) => 대충 10^6으로 조건안에 가능함.
*/

#include <stdio.h>

int N;
int dp[100][10][1024];

void init()
{
	scanf("%d", &N);

	for (int back = 1; back <= 9; back++)
		dp[0][back][1 << back] = 1;
}

int calc_num(int num1, int num2)
{
	return (num1 + num2) % 1000000000;
}

void calc_dp(int next_back, int before_back, int before_check, int n)
{
	int next_check = before_check | (1 << next_back);
	dp[n][next_back][next_check] = calc_num(dp[n][next_back][next_check], dp[n - 1][before_back][before_check]);
}

void solve()
{
	for (int n = 1; n < N; n++)
	{
		for (int check = 0; check < 1024; check++)
		{
			//back = 0
			calc_dp(0, 1, check, n);

			//back = 1 ~ 8
			for (int back = 1; back <= 8; back++)
			{
				calc_dp(back, back - 1, check, n);
				calc_dp(back, back + 1, check, n);
			}

			//back = 9
			calc_dp(9, 8, check, n);
		}
	}
}

void print_result()
{
	int result = 0;
	for (int back = 0; back <= 9; back++)
		result = calc_num(result, dp[N - 1][back][1023]);

	printf("%d", result);
}

int main()
{
	init();
	solve();
	print_result();

	return 0;
}