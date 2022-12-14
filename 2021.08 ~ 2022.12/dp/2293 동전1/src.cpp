/*
-풀이-

r\c		0	1	2	3	4	5	6	7	8	9	10
0(0)	1	0	0	0	0	0	0	0	0	0	0
1(1)	1	1	1	1	1	1	1	1	1	1	1
2(2)	1	1	2	2	3	3	4	4	5	5	6
3(5)	1	1	2	2	3	4	5	6	7	8	10

점화식: f(r, c) = f(r - 1, c) + f(r, c - 코인값(r))

-> 이걸 2차원 DP로 구현하면 메모리 제한에서 걸려버림. 메모리 최적화가 필요.
-> col만 고려한 1차원 배열을 row를 넘어가면서 덮어씀 
*/

/*
-포인트-

1. 2차원 dp 점화식 세우기
2. 1차원으로 메모리최적화
*/

#include <iostream>
#include <algorithm>
using namespace std;

int N, K;
int coin[101];
int dp[10001];

void init()
{
	cin >> N >> K;
	for (int i = 1; i <= N; i++)
		cin >> coin[i];

	sort(coin + 1, coin + N + 1);
	dp[0] = 1;
}

void getDp()
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= K; c++)
		{
			int term = c - coin[r];
			if (term < 0)
				continue;
			dp[c] += dp[term];
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	getDp();
	cout << dp[K];

	return 0;
}