#include <iostream>
using namespace std;

/*
-생각난 풀이방식

1. dp
2차원 배열에 각 칸에 도착할 수 있는 방법 수를 기록.
O(NxN)

2. dfs로 완전탐색
각 칸의 값에 따라 위치를 변경하는 함수를 만들어서 오른쪽 아래에 도착하는 경우의 수를 전부 체크.
하나의 칸에서 오른쪽과 아래 2개의 분기가 발생.
O(2^N) -> 너무 느림.
*/

int N; //4byte
int map[101][101]; //101 x 101 x 4 byte
unsigned long long dp[101][101]; // 101 x 101 x 8byte

void init()
{
	cin >> N;
	for (int row = 1; row <= N; row++)
	{
		for (int col = 1; col <= N; col++)
		{
			cin >> map[row][col];
		}
	}

	dp[1][1] = 1;
}

void solve()
{
	for (int row = 1; row <= N; row++)
	{
		for (int col = 1; col <= N; col++)
		{
			if (map[row][col] == 0)
				continue;

			int jumpRow = row + map[row][col];
			if (1 <= jumpRow && jumpRow <= N)
				dp[jumpRow][col] += dp[row][col];

			int jumpCol = col + map[row][col];
			if (1<= jumpCol && jumpCol <= N)
				dp[row][jumpCol] += dp[row][col];
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	solve();
	cout << dp[N][N];

	return 0;
}