/*
-Ǯ��-

r\c		0	1	2	3	4	5	6	7	8	9	10
0(0)	1	0	0	0	0	0	0	0	0	0	0
1(1)	1	1	1	1	1	1	1	1	1	1	1
2(2)	1	1	2	2	3	3	4	4	5	5	6
3(5)	1	1	2	2	3	4	5	6	7	8	10

��ȭ��: f(r, c) = f(r - 1, c) + f(r, c - ���ΰ�(r))

-> �̰� 2���� DP�� �����ϸ� �޸� ���ѿ��� �ɷ�����. �޸� ����ȭ�� �ʿ�.
-> col�� ����� 1���� �迭�� row�� �Ѿ�鼭 ��� 
*/

/*
-����Ʈ-

1. 2���� dp ��ȭ�� �����
2. 1�������� �޸�����ȭ
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