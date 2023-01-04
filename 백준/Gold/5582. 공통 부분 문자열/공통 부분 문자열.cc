/*
-문제정리

	가장 긴 공통부분문자열의 길이를 구하는 문제.

	입력으로 2개의 문자열이 주어짐.
	문자열의 길이는 1 ~ 4000

-풀이
	
	dp로 유명한 LCS알고리즘과 유사함.
	다만 LCS알고리즘은 3123의 부분 문자열로 32, 33, 313 등 연속하지 않아도 괜찮지만 이 문제에서는 꼭 연속한 문자열이어야 함.

	LCS처럼 dp[str1_idx][str2_idx]으로 구성되는 2차원 배열을 이용함.
	dp배열에는 LCS처럼 누적되는 값을 저장하는 것이 아니라 연속되지 않은 값이 나오면 0으로 리셋되는 방식을 사용함.(연속한 문자열을 표현하기 위함.)

	문자열1과 문자열2의 부분이 일치시
		dp[str1_idx][str2_idx] = dp[str1_idx - 1][str2_idx - 1] + 1
	일치하지 않으면 0으로 리셋
		dp[str1_idx][str2_idx] = dp[str1_idx - 1][str2_idx - 1]

	문자열의 부분이 일치할 때마다 max값을 새로 기록하면 최대 문자열 길이를 알 수 있음.

-메모리 최적화
	
	2차원 배열을 1차원 배열로 압축해서 사용함.
*/

#include <stdio.h>

char str1[4002], str2[4002];
int len1, len2;
int dp[4001][4001];
int result = 0;

int my_strlen(char* str)
{
	int len = 0;
	while (str[len] != '\0')
		len++;

	return len;
}

void init()
{
	scanf("%s %s", str1 + 1, str2 + 1);

	len1 = my_strlen(str1 + 1);
	len2 = my_strlen(str2 + 1);
}

void solve()
{
	for (int i = 1; i <= len1; i++)
	{
		for (int j = 1; j <= len2; j++)
		{
			if (str1[i] == str2[j])
			{
				dp[i][j] = dp[i - 1][j - 1] + 1;
				if (result < dp[i][j])
					result = dp[i][j];
			}
			else
				dp[i][j] = 0;
		}
	}
}

int main()
{
	init();
	solve();
	printf("%d", result);

	return 0;
}