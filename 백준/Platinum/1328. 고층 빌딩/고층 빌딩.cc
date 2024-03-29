/*
-문제 정리
	N개의 빌딩을 1열로 세울 수 있는 경우의 수를 구한다.
	N개의 빌딩은 1 ~ N의 높이를 가지고 높이가 같은 빌딩은 없다.
	왼쪽에서 봤을 때의 개수 L과 오른쪽에서 봤을 때의 개수 R이 주어짐.

	N은 1 ~ 100
	L, R은 1 ~ N

-풀이
	1. 완전탐색
		O(N!)이고 N이 1 ~ 100이므로 너무 느림.

	2. dp (첫번쨰 - 가장 높은 빌딩을 기준으로 생각)
		"1 ~ K개의 높이를 가지는 K개의 빌딩을 1열로 세워서 look개의 빌딩이 보이는 배치의 경우의 수"를 dp열에 저장
		dp[K][look]의 배치 구성을 다음과 같이 생각해 볼 수 있음.
			(1) dp[0 ~ K - 1][look - 1]을 구성하는 앞 부분. => dp배열의 값 그대로 사용
			(2) K의 높이를 가지는 가장 높은 벽. => 1
			(3) 어떤 배치든 상관없는 뒷 부분. => (1)과 (2)를 구성하고 남은 나머지 수의 팩토리얼만큼 경우의 수

		위의 규칙으로 만든 점화식은 다음과 같음.
		dp[K][look] = dp[0][look - 1] * (K - 1)! + dp[1][look - 1] * (K - 2)! + ... + dp[K - 1][look - 1] * 0!
		
		마지막에 왼쪽에서 L, 오른쪽에서 R개의 빌딩이 보이는 경우의 수는 아래의 식으로 계산함.
		result = (dp[0][L - 1] * dp[N - 1][R - 1] + dp[1][L - 1] * dp[N - 2][R - 1] + ... + dp[N - 1][L - 1] * dp[0][R - 1]) * (N - 1)!

		이 방법은 99!까지 계산에 들어가서 8바이트로도 계산결과를 담을 수 없음.

	3. dp (두번째 - 가장 낮은 빌딩을 기준으로 생각)
		dp[N][L][R]의 3차원 배열에 경우의 수를 저장.
		N은 빌딩의 수, L은 왼쪽에서 보이는 빌딩의 수, R은 오른쪽에서 보이는 빌딩의 수

		높이가 1인 빌딩을 추가하는 경우의 수를 다음과 같이 생각해 볼 수 있음.
			(1) 가장 왼쪽에 추가. => L이 무조건 1 증가함. R에 영향 x.
			(2) 중간에 추가. => L, R 값에 영향 X
			(3) 가장 오른쪽에 추가. => R이 무조건 1 증가함. L에 영향 x.

		위 규칙으로 만든 점화식은 다음과 같음.
		dp[N][L][R] = dp[N - 1][L - 1][R] + dp[N - 1][L][R - 1] + dp[N - 1][L][R] * (N - 2)

		이 방법이 가장 구현도 간편하면서 문제도 없음.

-주의사항
	경우의 수를 저장할 때 1000000007으로 나눈 나머지를 저장하므로 최대 1000000006이 dp값으로 저장됨.
	int로 담을 경우 *2까지는 괜찮지만 *3부터 오버플로우가 나버리므로 *100까지 버틸 수 있는 자료형으로 계산해야 함.

-메모리 최적화
	dp[N][L][R] = dp[N - 1][L - 1][R] + dp[N - 1][L][R - 1] + dp[N - 1][L][R] * (N - 2)의 점화식에서
	dp[N][][]과 dp[N - 1][][]만 사용되므로 메모리의 사용량을 줄일 수 있음.
	N부분에는 2개의 인덱스만 부여해서 홀수, 짝수로 구분해서 사용.
*/

#include <stdio.h>

int N, L, R;
int dp[2][101][101];

void init()
{
	scanf("%d %d %d", &N, &L, &R);
	dp[1][1][1] = 1;
}

void solve()
{
	for (int num = 2; num <= N; num++)
	{
		int before = (num - 1) % 2;
		int curr = num % 2;
	
		for (int left = 1; left <= num; left++)
		{
			for (int right = 1; right <= num; right++)
			{
				dp[curr][left][right] = ((unsigned long long)dp[before][left - 1][right] + (unsigned long long)dp[before][left][right - 1]	+ (unsigned long long)dp[before][left][right] * ((unsigned long long)num - 2)) % 1000000007ULL;
			}
		}
	}
}

int main()
{
	init();
	solve();
	printf("%d", dp[N % 2][L][R]);

	return 0;
}