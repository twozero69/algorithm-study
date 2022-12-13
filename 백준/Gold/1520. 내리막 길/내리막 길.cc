#include <iostream>
using namespace std;

int M, N;
int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };
int map[501][501];
int dp[501][501];
bool check[501][501];

void init()
{
	cin >> M >> N;
	for (int r = 1; r <= M; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			cin >> map[r][c];
		}
	}

	dp[1][1] = 1;
	check[1][1] = true;
}

int getDp(int row, int col)
{
	if (check[row][col])
		return dp[row][col];

	for (int dir = 0; dir < 4; dir++)
	{
		int neighborRow = row + dy[dir];
		if (neighborRow <= 0 || neighborRow > M)
			continue;

		int neighborCol = col + dx[dir];
		if (neighborCol <= 0 || neighborCol > N)
			continue;

		if (map[neighborRow][neighborCol] <= map[row][col])
			continue;

		dp[row][col] += getDp(neighborRow, neighborCol);
	}
	check[row][col] = true;
	return dp[row][col];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	init();
	cout << getDp(M, N);

	return 0;
}