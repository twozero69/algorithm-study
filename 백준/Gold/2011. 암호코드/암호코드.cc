/*
-풀이
	dp배열에 해당 문자까지의 해석 경우의 수를 기록.
	
	x0:		x가 1~2면 10, 20으로 해석. -> dp(n) = dp(n - 2)
			x가 0, 3~9면 에러.

	x1~6:	x가 1~2면 2가지로 해석가능해짐. -> dp(n) = dp(n - 2) + dp(n - 1)
			x가 0, 3~9면 C~I로 해석. -> dp(n) = dp(n - 1)

	x7~9:	x가 1이면 2가지로 해석가능해짐. -> dp(n) = dp(n - 2) + dp(n - 1)
			x가 0, 2~9면 B~I로 해석. -> dp(n) = dp(n - 1)

-메모리 최적화
	dp(n), dp(n - 2), dp(n - 1)만 사용하므로 변수 3개만 사용하는 것으로 최적화.

-입출력 기본
	scanf()의 리턴 = 매칭된 수 또는 EOF
	리턴값이 매칭된 수에 비해 모자르면 잘 매칭되지않은 입력이 있는 것.
	EOF는 파일을 끝까지 읽었을 때 리턴 정수값으로는 -1임.
	
	시스템콜로 read많이 써봐서 알고 있겠지만 엔터치면 입력버퍼에 '\n'까지 들어감.
	EOF까지 읽는 것으로 해버리면 \n이 들어가버리니 주의.
*/

#include <stdio.h>

char string[5000];
int string_size;
int dp_n, dp_n_1, dp_n_2;

void init()
{
	while (scanf("%c", &string[string_size]) != EOF && string[string_size] != '\n')
		string_size++;

	if (string_size == 0 || string[0] == '0')
		return;

	dp_n_1 = 1;
	dp_n = 1;
}

void solve()
{
	for (int i = 1; i < string_size; i++)
	{
		char current = string[i];
		char before = string[i - 1];
		dp_n_2 = dp_n_1;
		dp_n_1 = dp_n;
		
		if (current == '0')
		{
			if (before == '0' || '3' <= before)
			{
				dp_n = 0;
				return;
			}

			dp_n_1 = dp_n;
			dp_n = dp_n_2;
		}
		else if ('1'<= current && current <= '6')
		{
			int term = dp_n;
			if ('1' <= before && before <= '2')
				dp_n = (dp_n_2 + dp_n_1) % 1000000;
			else
				dp_n = dp_n_1;

			dp_n_1 = term;
		}
		else if ('7' <= current)
		{
			int term = dp_n;
			if (before == '1')
				dp_n = (dp_n_2 + dp_n_1) % 1000000;
			else
				dp_n = dp_n_1;

			dp_n_1 = term;
		}
	}
}

int main()
{
	init();
	if (dp_n == 1)
		solve();
	printf("%d", dp_n);

	return 0;
}