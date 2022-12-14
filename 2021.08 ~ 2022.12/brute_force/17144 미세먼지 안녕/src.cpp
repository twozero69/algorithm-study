#include <iostream>
using namespace std;

int R, C, T;
int dust[50][50];
int dy[4] = { 0, 0, -1, 1 };
int dx[4] = { -1, 1, 0, 0 };
int airCleanerRow1, airCleanerRow2;

void init()
{
	cin >> R >> C >> T;

	for (int row = 0; row < R; row++)
	{
		for (int col = 0; col < C; col++)
		{
			cin >> dust[row][col];
		}
	}

	for (int row = 0; row < R; row++)
	{
		if (dust[row][0] == -1)
		{
			airCleanerRow1 = row;
			airCleanerRow2 = row + 1;
			break;
		}
	}
}

void spreadDust()
{
	int term[50][50];
	for (int row = 0; row < R; row++)
	{
		for (int col = 0; col < C; col++)
		{
			term[row][col] = dust[row][col];
		}
	}

	for (int row = 0; row < R; row++)
	{
		for (int col = 0; col < C; col++)
		{
			if (term[row][col] <= 0)
				continue;
			int someDust = term[row][col] / 5;
			for (int i = 0; i < 4; i++)
			{
				int newRow = row + dy[i];
				int newCol = col + dx[i];
				if (newRow < 0 || newRow >= R)
					continue;
				if (newCol < 0 || newCol >= C)
					continue;
				if (dust[newRow][newCol] == -1)
					continue;
				dust[row][col] -= someDust;
				dust[newRow][newCol] += someDust;
			}
		}
	}
}

void cleanDust()
{
	for (int row = airCleanerRow1 - 1; row > 0; row--)
	{
		dust[row][0] = dust[row - 1][0];
	}

	for (int row = airCleanerRow2 + 1; row < R - 1; row++)
	{
		dust[row][0] = dust[row + 1][0];
	}

	for (int col = 0; col < C - 1; col++)
	{
		dust[0][col] = dust[0][col + 1];
		dust[R - 1][col] = dust[R - 1][col + 1];
	}

	for (int row = 0; row < airCleanerRow1; row++)
	{
		dust[row][C - 1] = dust[row + 1][C - 1];
	}

	for (int row = R - 1; row > airCleanerRow2; row--)
	{
		dust[row][C - 1] = dust[row - 1][C - 1];
	}

	for (int col = C - 1; col >= 2; col--)
	{
		dust[airCleanerRow1][col] = dust[airCleanerRow1][col - 1];
		dust[airCleanerRow2][col] = dust[airCleanerRow2][col - 1];
	}

	dust[airCleanerRow1][1] = 0;
	dust[airCleanerRow2][1] = 0;
}

void printResult()
{
	int result = 0;
	for (int row = 0; row < R; row++)
	{
		for (int col = 0; col < C; col++)
		{
			if (dust[row][col] == -1)
				continue; 
			result += dust[row][col];
		}
	}
	cout << result;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	init();
	for (int i = 0; i < T; i++)
	{
		spreadDust();
		cleanDust();
	}
	printResult();

	return 0;
}