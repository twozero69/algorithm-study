/*
-문제 정리
	모든 노드를 방문하는 최소비용 경로구하기.
	한번 갔던 경로는 재방문 x.
	반드시 1개 이상의 경로가 존재하도록 입력이 구성됨.

-풀이
	1. 완전탐색
		순환하면서 모든 경로에 대해서 완전탐색.
		한번 방문한 노드를 재방문 불가하므로 O(N!) -> 너무느림.
	
	2. 비트마스킹을 사용한 dp
		dp[16][1 << 16]의 배열을 준비.
		첫번째 인덱스는 이번에 방문한 노드의 번호.
		두번째 인덱스는 이전에 방문한 노드의 방문체크임.
		'1111 1111 1111 1111(2)'이면 16개의 노드를 모두 방문했다는 의미.
		dp배열에 방문체크의 노드들을 방문 후 다음 노드를 방문할 때 비용의 최소값을 저장.
		단 0번 노드에서만 출발하고 0번 노드에서 끝난다고 제한.

		점화식: dp[n][check] = dp[m][check & ~(1 << m)] + cost[m][n] 중에서 최소값(m = check에 있는 m번째 bit)
		2중 for문으로 check, n을 순회하면서 dp배열을 작성.
		시작부분과 끝부분은 0에서 출발, 0에서 종료로 정해놓고 dp배열을 작성.
*/

#include <stdio.h>

int N; //노드의 수 2~16
int W[16][16]; //비용[출발노드][도착노드]
int dp[16][1 << 16]; //[방문한 노드][방문체크]

void init()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			scanf("%d", &W[i][j]);
		}
	}
}

int bit_count(unsigned int check)
{
	int count = 0;
	while (check)
	{
		count += check % 2;
		check >>= 1;
	}
	
	return count;
}

void solve()
{
	//bit_count = 1
	//출발은 0번 노드에서 시작.
	for (int i = 0; i < N; i++)
		dp[i][1 << 0] = W[0][i];

	//bit_count = 2 ~ N-1
	unsigned int check_end = (1 << N) - 1;
	for (unsigned int check = 0; check < check_end; check++)
	{
		if (bit_count(check) < 2)
			continue;

		for (int node = 0; node < N; node++)
		{
			if (check & (1 << node))
				continue;

			for (int before = 0; before < N; before++)
			{
				if (node == before || !(check & (1 << before)))
					continue;

				if (dp[before][check & ~(1 << before)] == 0 || W[before][node] == 0)
					continue;
				
				int term = dp[before][check & ~(1 << before)] + W[before][node];
				if (dp[node][check] == 0 || dp[node][check] > term)
					dp[node][check] = term;
			}
		}
	}

	//bit_count = N
	//마지막에 다시 0번 노드로 돌아감.
	for (int before = 1; before < N; before++)
	{
		if (dp[before][check_end & ~(1 << before)] == 0 || W[before][0] == 0)
			continue;

		int term = dp[before][check_end & ~(1 << before)] + W[before][0];
		if (dp[0][check_end] == 0 || dp[0][check_end] > term)
			dp[0][check_end] = term;
	}
}

int main()
{
	init();
	solve();
	printf("%d", dp[0][(1 << N) - 1]);

	return 0;
}